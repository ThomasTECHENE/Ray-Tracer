#include "boxRM.hpp"
#include "Intersection.hpp"
#include "rayon.hpp"

BoxRM::BoxRM(glm::vec3 pos, glm::vec3 dim){
	position = pos;
	dimension = dim;
}

bool BoxRM::calculIntersection(const Rayon &r, Intersection &I){
	glm::vec3 rd = r.Vect();
	glm::vec3 r0 = r.Orig();

	float tmin = 1;
	float tmax = 250;

	float precision = 0.05f;
	float t = tmin;


	for (int i = 0; i < 250; i++){
		float resultat = map(r0 + rd*t);
		if (resultat < precision || t > tmax){
			break;
		}
		t += resultat;
	}

	if (t > tmax){ return false; }
	else {
		Intersection inter;
		inter.dist = t;
		inter.normal = calcNormale(r0 + rd*t);
		inter.Objet = this;
		I = inter;
		return true;
	}
}

glm::vec3 BoxRM::calcNormale(glm::vec3 pos){
	glm::vec3 v = glm::vec3(0.001, 0.0, 0.0);
	glm::vec3 normale = glm::vec3(
		map(pos + glm::vec3(v.x, v.y, v.y)) - map(pos - glm::vec3(v.x, v.y, v.y)),
		map(pos + glm::vec3(v.y, v.x, v.y)) - map(pos - glm::vec3(v.y, v.x, v.y)),
		map(pos + glm::vec3(v.y, v.y, v.x)) - map(pos - glm::vec3(v.y, v.y, v.x)));
	return glm::normalize(normale);
}

float BoxRM::map(glm::vec3 x){
	return distBox(x - position, dimension);
}

float BoxRM::distBox(glm::vec3 pos, glm::vec3 dim){
	glm::vec3 tmp = glm::abs(pos) - dim;
	return glm::min(glm::max(tmp.x, glm::max(tmp.y, tmp.z)), 0.0f) + glm::length(glm::max(tmp, 0.0f));
}

glm::vec3 BoxRM::twist(glm::vec3 p){
	float c = glm::cos(0.6*p.y + 0.0);
	float s = glm::sin(0.6*p.y + 0.0);
	glm::vec2 p2 = glm::vec2(p.x, p.z);
	glm::mat2 m = glm::mat2(c, -s, s, c);
	return glm::vec3(p.y, m*p2);
}