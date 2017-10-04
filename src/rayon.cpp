#include "rayon.hpp"
#include "Objet3D.hpp"
#include "plan.hpp"
#include "Scene.hpp"
#include "triangle.hpp"

#include <vector>
// --------------------------------------------------------------------------
//
// Methodes (et operations) sur les rayons
//
// --------------------------------------------------------------------------

glm::vec3 Rayon::Lancer(Scene &sc, int recur) const{
	
	glm::vec3 res; // Couleur resultante

	// Au depart, le point au bout du rayon est noir
	res = glm::vec3(0, 0, 0);

	if (recur < 0){ return res; }	

	// Calcul des intersections du rayon avec la scène
	Intersection intersectionPlusProche, intTemp;
	intersectionPlusProche.dist = INFINITY;
	intTemp.dist = INFINITY;
	for (int i = 0; i < sc.listObjets.size(); i++){
		sc.listObjets[i]->calculIntersection(*this, intTemp);
		if (intTemp.dist < intersectionPlusProche.dist){
			intersectionPlusProche = intTemp;
		}
	}

	//Pas d'intersection
	if (isinf(intersectionPlusProche.dist)){ return res; }

	// Calculer et retourner la couleur du rayon
	Objet3D* Obj = intersectionPlusProche.Objet;
	
	//COMPOSANTE AMBIANTE
	glm::vec3 ambiant = Obj->material->setAmbiant(Obj->material->Cambiant, Obj->material->ka);

	//REFLECTION PARFAITE
	glm::vec3 reflection;
	if (Obj->material->krefl == 1.0f){
		reflection = getReflectRay(intersectionPlusProche, *this).Lancer(sc, recur - 1);
	}

	//REFLECTION DIFFUSE
	if (Obj->material->krefl > 0.0f && Obj->material->krefl != 1.0f){
		glm::vec3 accColorReflection; /*= glm::vec3(0);*/
		glm::vec3 accDot, ColorReflection;
		float dotArecup;
		float samples = 300.0f;
		for (int i = 0; i < samples; i++){
			ColorReflection = getDiffuseReflectRay(intersectionPlusProche, *this, dotArecup).Lancer(sc, recur - 3);
			accColorReflection += ColorReflection*dotArecup;
			accDot += dotArecup;
		}
		reflection = accColorReflection / accDot;
		reflection *= 0.7f;
	}

	//REFRACTION
	glm::vec3 refraction;
	if (Obj->material->indiceRefrac > 0.0f) {
		float angle = glm::dot(intersectionPlusProche.normal, this->vect);
		bool inside = false;
		if (-angle < 0){ inside = true; }
		else{ inside = false; }
		glm::vec3 refractedColor = getRefractRay(intersectionPlusProche, *this, Obj->material->indiceRefrac, inside).Lancer(sc, recur - 1);
		//loi de beer
		glm::vec3 absorbance = Obj->material->Cdiffuse * 0.15f * -(intersectionPlusProche.dist);
		glm::vec3 transparence = glm::vec3(glm::exp(absorbance.r), glm::exp(absorbance.g), glm::exp(absorbance.b));
		refraction = refractedColor * transparence;
	}
	//HARDSHADOWS
	Intersection interHardshadows;
	Rayon r = getShadowRay(intersectionPlusProche, *this, sc.light.position);
	float distanceLumiere = glm::length(sc.light.position - r.orig);
	bool ombre = false;
	for (int i = 0; i < sc.listObjets.size(); i++)
	{
		// Determiner si le point est dans l'ombre (calcul du nombres d'obstacles entre le point d'intersection et la lumiere)
		sc.listObjets[i]->calculIntersection(r, interHardshadows);
		if (interHardshadows.dist > 0){
			if (interHardshadows.dist < distanceLumiere){
				ombre = true;
				break;
			}
		}
		if (ombre){ break; }
	}
	
	//SOFTSHADOWS
	
	/*float samplesomb = 300.0f;
	float accIntensité = 0.0f;
	float distanceLumiere;
	bool ombre = false;
	glm::vec3 posRandom;
		for (int j = 0; j < samplesomb; j++){
			Intersection interSoftshadows;
			ombre = false;
			posRandom = randPosAreaLightGLM(sc.light.position, glm::sphericalRand(3.0f));
			//posRandom = randPosAreaLight(sc.light.position);
			Rayon r = getShadowRay(intersectionPlusProche, *this, posRandom);
			distanceLumiere = glm::length(posRandom - r.orig);
			for (int i = 0; i < sc.listObjets.size(); i++){
				sc.listObjets[i]->calculIntersection(r, interSoftshadows);
				if (interSoftshadows.dist > 0){
					if (interSoftshadows.dist < distanceLumiere){
						ombre = true;
						break;
					}
				}
			}
			if (!ombre){ accIntensité += 1; }
		}

	accIntensité = accIntensité/samplesomb;*/

	//ATTENUATION DE LA LUMIERE
	glm::vec3 posIntersection = this->orig + this->vect*intersectionPlusProche.dist;
	float lightPower = 20.0f;
	glm::vec3 vectPointLumiere = (sc.light.position - posIntersection);
	float distPointLumiere = (glm::length(vectPointLumiere));
	float attenuation = lightPower / (1.0 + 0.1*distPointLumiere + 0.01*distPointLumiere*distPointLumiere);
	
	//SI LE POINT EST DANS L OMBRE ON NE RETOURNE PAS LES COMPOSANTES DIFFUSE ET SPECULAIRE(HARDSHADOWS)
	if (ombre){ return res = ambiant + reflection*Obj->material->krefl + refraction*Obj->material->krefr; }

	//COMPOSANTE DIFFUSE
	glm::vec3 diffuse = Obj->material->setDiffuse(Obj->material->Cdiffuse, Obj->material->kd, Orig(), Vect(), intersectionPlusProche.normal, intersectionPlusProche.dist, sc.light.position, sc.light2.position);
	//COMPOSANTE SPECULAIRE
	glm::vec3 speculaire = Obj->material->setSpeculaire(Obj->material->Cspecular, Obj->material->ks, Orig(), Vect(), intersectionPlusProche.normal, intersectionPlusProche.dist, sc.light.position, sc.light2.position);
	
	//res pour hardshadows OU sans shadows
	res = (ambiant + diffuse*attenuation + speculaire*attenuation) + reflection*Obj->material->krefl + refraction*Obj->material->krefr;
	
	//res pour softshadows
	//res = (ambiant + diffuse*accIntensité*attenuation + speculaire*accIntensité*attenuation) + reflection*Obj->material->krefl + refraction*Obj->material->krefr;
	return res;
}

//fonction de récupération du rayon réfléchi
Rayon Rayon::getReflectRay(Intersection inter, Rayon ray) const{
	glm::vec3 pt = ray.orig + ray.vect*inter.dist;
	Rayon reflectRay;
	reflectRay.Vect(glm::normalize(glm::reflect(ray.vect, inter.normal)));
	reflectRay.Orig(pt + reflectRay.vect*EPSILON);
	return reflectRay;
}

//fonction de récupération des rayons de reflexion diffuse
Rayon Rayon::getDiffuseReflectRay(Intersection inter, Rayon ray, float &dot) const{
	glm::vec3 pt = ray.orig + ray.vect*inter.dist;
	Rayon diffuseReflectRay;
	glm::vec3 dirTmp = glm::normalize(glm::reflect(ray.vect, inter.normal));
	bool rayFound = false;
		while (!rayFound){
			glm::vec3 sphericalDir = uniformSamplingSphere(dirTmp);
			float angle = glm::dot(dirTmp, sphericalDir);
			if (angle > 0.93f){
				diffuseReflectRay.Vect(sphericalDir);
				dot = angle;
				rayFound = true;
			}
		}
	diffuseReflectRay.Orig(pt + diffuseReflectRay.vect*EPSILON);
	return diffuseReflectRay;
}

//fonction de récupération de rayon réfracté
Rayon Rayon::getRefractRay(Intersection inter, Rayon ray, float indice, bool ins) const{
	glm::vec3 pt = ray.orig + ray.vect*inter.dist;
	Rayon refractRay;
	if (ins){ 
		glm::vec3 N = -inter.normal;
		refractRay.Vect(glm::normalize(glm::refract(ray.vect, N, (indice / indRefractionVide))));
	}
	else{
		refractRay.Vect(glm::normalize(glm::refract(ray.vect, inter.normal, (indRefractionVide/indice))));
	}
	refractRay.Orig(pt + refractRay.vect*EPSILON);
	return refractRay;
}

//fonction de récupération de rayon d'ombre
Rayon Rayon::getShadowRay(Intersection inter, Rayon ray, glm::vec3 posLight) const{
	glm::vec3 pt = ray.orig + ray.vect*inter.dist;
	Rayon shadowRay;
	shadowRay.Vect(glm::normalize(posLight - pt));
	shadowRay.Orig(pt + shadowRay.vect*EPSILON);
	return shadowRay;
}

/*Ancienne version pour avoir zone de lumière
glm::vec3 Rayon::randPosAreaLight(glm::vec3 posLight)const{
	float high = 3.0f;
	float low = -3.0f;
	float x = low + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (high - low)));
	float y = low + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (high - low)));
	float z = low + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (high - low)));
	glm::vec3 pos = glm::vec3(posLight.x + x, posLight.y + y, posLight.z + z);
	return pos;
}*/

//récupération de la zone de lumiere pour les ombres douces
glm::vec3 Rayon::randPosAreaLightGLM(glm::vec3 posLight, glm::vec3 dist)const{
	return glm::vec3(posLight.x + dist.x, posLight.y + dist.y, posLight.z + dist.z);
}

//fonction de récupération de direction de rayon dans l'hemisphere superieur au point d'intersection
glm::vec3 Rayon::uniformSamplingSphere(glm::vec3 normal)const{
	int counter = 0;
	while (true)
	{
		float x = static_cast <float> (rand()) / (static_cast <float> (RAND_MAX));
		float y = static_cast <float> (rand()) / (static_cast <float> (RAND_MAX));
		float z = static_cast <float> (rand()) / (static_cast <float> (RAND_MAX));
		glm::vec3 vectSampled = glm::vec3(x - 0.5f, y - 0.5f, z - 0.5f);
		vectSampled = glm::normalize(vectSampled);
		if (glm::dot(vectSampled, normal) > 0.0f){
			return vectSampled;
		}
	}
}
