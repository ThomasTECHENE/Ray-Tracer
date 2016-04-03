#include "Material.hpp"

void Material::setMaterial(glm::vec3 Ca, glm::vec3 Cd, glm::vec3 Cs, int shine, float kr, float indRefr, float krefr){
	Cambiant = Ca*ka;
	Cdiffuse = Cd;
	Cspecular = Cs;
	shininess = shine;
	krefl = kr;
	indiceRefrac = indRefr;
	this->krefr = krefr;
}

glm::vec3 Material::setAmbiant(glm::vec3 Ca, float ka){
	glm::vec3 a = Ca*ka;
	return a;
}

glm::vec3 Material::setDiffuse(glm::vec3 Cd, float kd, glm::vec3 orig, glm::vec3 vect, glm::vec3 normal,float dist, glm::vec3 posLumiere, glm::vec3 posLumiere2){
	glm::vec3 posIntersection = orig + vect*dist;
	glm::vec3 vectLum = glm::normalize(posLumiere - posIntersection);
	//glm::vec3 vectLum2 = glm::normalize(posLumiere2 - posIntersection);
	glm::vec3 d = Cd*kd*glm::dot(normal, vectLum) /*+
		Cd*kd*glm::dot(normal, vectLum2)*/;
	return d;
}

glm::vec3 Material::setSpeculaire(glm::vec3 Cs, float ks, glm::vec3 orig, glm::vec3 vect, glm::vec3 normal, float dist, glm::vec3 posLumiere, glm::vec3 posLumiere2){
	glm::vec3 posIntersection = orig + vect*dist;
	glm::vec3 vectLum = glm::normalize(posLumiere - posIntersection);
	//glm::vec3 vectLum2 = glm::normalize(posLumiere2 - posIntersection);
	glm::vec3 vectReflechi = glm::normalize(2 * (glm::dot(normal, vectLum))*normal - vectLum);
	//glm::vec3 vectReflechi2 = glm::normalize(2 * (glm::dot(normal, vectLum2))*normal - vectLum2);
	glm::vec3 vectVue = glm::normalize(posIntersection - orig);
	glm::vec3 s = Cs*ks*glm::pow(glm::max(glm::dot(vectReflechi, -vectVue), 0.0f), shininess) /*+
		Cs*ks*glm::pow(glm::max(glm::dot(vectReflechi2, -vectVue), 0.0f), shininess)*/;
	return s;
}

