#ifndef SPHERE_HPP
#define SPHERE_HPP

#include "Objet3D.hpp"

class Sphere : public Objet3D
{
public:
	Sphere(){};
	~Sphere(){};
	Sphere(glm::vec3 centreS, const float radius);

	float radius;
	glm::vec3 ptIntersection, centre;

	//points pour calcul du déterminant
	float a, b, c;
	float discriminant;
	float t0, t1;

	virtual bool calculIntersection(const Rayon &, Intersection &I);
};
#endif //!PLAN_HPP