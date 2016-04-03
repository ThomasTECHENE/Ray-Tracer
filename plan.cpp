#include "plan.hpp"
#include "rayon.hpp"
#include "Intersection.hpp"

Plan::Plan(glm::vec3 normaleAuPlan, float d){
	/*a = normaleAuPlan.x;
	b = normaleAuPlan.y;
	c = normaleAuPlan.z;*/
	normale = normaleAuPlan;
	this->d = d;
}

Plan::Plan(glm::vec3 &p1, glm::vec3 &p2, glm::vec3 &p3){
	glm::vec3 normale = glm::normalize(glm::cross(p2 - p1, p3 - p1));
	a = normale.x;
	b = normale.y;
	c = normale.z;
	d = -(glm::dot(p1, normale));
}

void Plan::tournerPlan(){
	a = -a;
	b = -b;
	c = -c;
	d = -d;
}

bool Plan::calculIntersection(const Rayon &r, Intersection &I){
	direction = r.Vect();
	origine = r.Orig();
	Intersection inter;
	//glm::vec3 normale_Plan = glm::vec3(this->a, this->b, this->c);

	vD = (glm::dot(normale, direction));
	v0 = -(glm::dot(normale, origine) + this->d);
	distance = (v0 / vD);
	//si plan derriere l'origine
	if (distance <= 0){
		inter.dist = INFINITY;
		inter.Objet = this;
		inter.normal = glm::vec3(0, 0, 0);
		I = inter;
		return false; 
	}
	//ajouter l'intersection à la liste d'intersection
	inter.dist = distance;
	inter.Objet = this;
	inter.normal = normale;
	I = inter;
	return true;
};