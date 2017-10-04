#ifndef ROUNDBOXRM_HPP
#define ROUNDBOXRM_HPP

#include "Objet3D.hpp"

class RoundBoxRM : public Objet3D
{
public:
	RoundBoxRM(glm::vec3 pos, glm::vec3 dim, float r);
	~RoundBoxRM(){};
	glm::vec3 position;
	glm::vec3 dimension;
	float rayon;


	float distRoundBox(glm::vec3 pos, glm::vec3 dim, float r);
	float map(glm::vec3 pos);
	glm::vec3 calcNormale(glm::vec3 pos);

	virtual bool calculIntersection(const Rayon &, Intersection &I);
};
#endif //!ROUNDBOXRM_HPP