#ifndef BOXRM_HPP
#define BOXRM_HPP

#include "Objet3D.hpp"

class BoxRM : public Objet3D
{
public:
	BoxRM(glm::vec3 pos, glm::vec3 dim);
	~BoxRM(){};
	glm::vec3 position;
	glm::vec3 dimension;

	float distBox(glm::vec3 pos, glm::vec3 dim);
	float map(glm::vec3 pos);
	glm::vec3 calcNormale(glm::vec3 pos);
	virtual bool calculIntersection(const Rayon &, Intersection &I);
	glm::vec3 twist(glm::vec3 pos);
};
#endif //!BOXRM_HPP