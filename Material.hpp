#ifndef MATERIAL_HPP
#define MATERIAL_HPP

#include <iostream>
#include <glm/glm.hpp>
#include "Intersection.hpp"

class Material{
public:
	Material(){};
	~Material(){};
	glm::vec3 Cambiant;
	glm::vec3 Cdiffuse;
	glm::vec3 Cspecular;
	int shininess;
	float ka = 0.2f;
	float kd = 0.8f;
	float ks = 0.8f;
	float krefl;
	float krefr;
	float indiceRefrac;


	void setMaterial(glm::vec3 Ca, glm::vec3 Cd, glm::vec3 Cs, int shine, float kr, float indRefr, float krefr);
	glm::vec3 setAmbiant(glm::vec3, float);
	glm::vec3 setDiffuse(glm::vec3, float, glm::vec3, glm::vec3, glm::vec3, float, glm::vec3, glm::vec3);
	glm::vec3 setSpeculaire(glm::vec3, float, glm::vec3, glm::vec3, glm::vec3, float, glm::vec3, glm::vec3);
};
#endif // !MATERIAL_HPP