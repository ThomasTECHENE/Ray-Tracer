#ifndef PLAN_HPP
#define PLAN_HPP

#include "Objet3D.hpp"

class Plan : public Objet3D
{
public:
	Plan(){};
	~Plan(){};
	Plan(glm::vec3 normaleAuPlan, float d);
	Plan(glm::vec3 &p1, glm::vec3 &p2, glm::vec3 &p3);
	glm::vec3 normale;
	
	//Constructeur du plan avec 3 points
	
	void tournerPlan();
	virtual bool calculIntersection(const Rayon &, Intersection &I);
	float distance, vD, v0;
	float a, b, c, d;
	glm::vec3 direction, origine;
private:

};
#endif // !PLAN_HPP
