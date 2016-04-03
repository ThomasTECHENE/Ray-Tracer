#ifndef TORUSRM_HPP
#define TORUSRM_HPP

#include "Objet3D.hpp"

class TorusRM : public Objet3D
{
public:
	TorusRM(glm::vec3 pos, glm::vec2 dim);
	~TorusRM(){};
	glm::vec3 position;
	glm::vec2 dimension;

	float distTorus(glm::vec3 pos, glm::vec2 dim);
	float map(glm::vec3 pos);
	glm::vec3 calcNormale(glm::vec3 pos);
	glm::vec3 twist(glm::vec3 p);
	virtual bool calculIntersection(const Rayon &, Intersection &I);
};
#endif; //!TORUSRM_HPP
