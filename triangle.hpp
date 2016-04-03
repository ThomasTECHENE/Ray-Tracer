#ifndef TRIANGLE_HPP
#define TRIANGLE_HPP

#include "Objet3D.hpp"
#include "const.hpp"

class Triangle : public Objet3D
{
public:
	
	glm::vec3 V0, V1, V2, normale;

	Triangle();
	~Triangle();
	Triangle(glm::vec3 a, glm::vec3 b, glm::vec3 c);
	//bool Inside(glm::vec3 P);
	virtual bool calculIntersection(const Rayon &, Intersection &I);
private:

};

#endif // !TRIANGLE_HPP