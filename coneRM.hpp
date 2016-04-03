#ifndef CONERM_HPP
#define CONERM_HPP

#include "Objet3D.hpp"

class ConeRM : public Objet3D
{
public:
	ConeRM(glm::vec3 pos, glm::vec3 dim);
	~ConeRM(){};
	glm::vec3 position;
	glm::vec3 dimension;

	float distCone(glm::vec3 pos, glm::vec3 dim);
	float map(glm::vec3 pos);
	glm::vec3 calcNormale(glm::vec3 pos);
	virtual bool calculIntersection(const Rayon &, Intersection &I);
};
#endif; //!CONERM_HPP