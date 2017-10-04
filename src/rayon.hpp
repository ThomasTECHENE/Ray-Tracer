#ifndef RAYON_HPP_
#define RAYON_HPP_

#include <glm/glm.hpp>
#include <glm/gtc/random.hpp>
#include "Scene.hpp"
#include "const.hpp"

class Rayon {
protected:

	glm::vec3 orig; // Origine du rayon
	glm::vec3 vect; // Vecteur directeur (oriente) du rayon

private:
	
	

public:
	float indRefractionVide = 1.0;
	Rayon() {	}

	// Lecture
	glm::vec3 Orig() const {
		return orig;
	}
	glm::vec3 Vect() const {
		return vect;
	}

	// Ecriture
	void Orig(const glm::vec3 & o) {
		orig = o;
	}
	void Vect(const glm::vec3 & v) {
		vect = glm::normalize(v);
	}

	glm::vec3 Lancer(Scene &sc,int current) const;
	Rayon getReflectRay(Intersection inter,Rayon incomingRay) const;
	Rayon getDiffuseReflectRay(Intersection inter, Rayon incomingRay, float &dot)const;
	Rayon getRefractRay(Intersection inter, Rayon incomingRay, float indice, bool ins) const;
	Rayon getShadowRay(Intersection inter, Rayon incomingRay, glm::vec3 posLight) const;
	glm::vec3 randPosAreaLight(glm::vec3 posLight)const;
	glm::vec3 randPosAreaLightGLM(glm::vec3 posLight, glm::vec3 dist)const;
	glm::vec3 uniformSamplingSphere(glm::vec3 normal)const;
	glm::vec3 uniformSamplingCone(glm::vec3 vect)const;

};

#endif /* RAYON_HPP_ */
