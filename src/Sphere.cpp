#include "Sphere.hpp"
#include "rayon.hpp"
#include "Intersection.hpp"

Sphere::Sphere(glm::vec3 centreS, const float radius){
	centre = centreS;
	this->radius = radius;
}

bool Sphere::calculIntersection(const Rayon &r, Intersection &I){
	glm::vec3 direction = r.Vect();
	glm::vec3 origine = r.Orig();
	Intersection inter, inter2;
	//calcul du déterminant de l'équation de seconde degré
	glm::vec3 diff = origine - centre;
	a = 1;
	b = 2 * (glm::dot(direction, (diff)));
	c = glm::dot(diff, diff) - glm::pow(radius, 2);
	discriminant = glm::pow(b, 2) - 4 * (a*c);
	if (discriminant < 0){
		return false;
	}

	if (discriminant == 0){
		t0 = (-b) / (2 * a);
		ptIntersection = origine + (direction * t0);
		inter.dist = t0;
		inter.Objet = this;
		inter.normal = (ptIntersection - centre) / radius;
		I = inter;
		return true;
	}

	if (discriminant > 0){
		t0 = (-b - glm::sqrt(discriminant)) / 2;
		t1 = (-b + glm::sqrt(discriminant)) / 2;
		if (t0 < t1 && t0 > 0){
			ptIntersection = origine + (direction * t0);
			inter.dist = t0;
			inter.Objet = this;
			inter.normal = (ptIntersection - centre) / radius;
			//I.push_back(inter);
			I = inter;
			return true;
		}
		if (t1 > t0 && t1 > 0){
			ptIntersection = origine + (direction * t1);
			inter.dist = t1;
			inter.Objet = this;
			inter.normal = (ptIntersection - centre) / radius;
			//I.push_back(inter);
			I = inter;
			return true;
		}
	}
}