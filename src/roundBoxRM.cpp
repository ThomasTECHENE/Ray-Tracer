#include "roundBoxRM.hpp"
#include "Intersection.hpp"
#include "rayon.hpp"

RoundBoxRM::RoundBoxRM(glm::vec3 pos, glm::vec3 dim, float r){
	position = pos;
	dimension = dim;
	rayon = r;
}

bool RoundBoxRM::calculIntersection(const Rayon &r, Intersection &I){
	glm::vec3 rd = r.Vect();
	glm::vec3 r0 = r.Orig();

	float tmin = 1;
	float tmax = 200;

	float precision = 0.05f;
	float t = tmin;


	for (int i = 0; i < 200; i++){
		float resultat = map(r0 + rd*t);
		if (resultat < precision || t > tmax){
			break;
		}
		t += resultat;
	}

	if (t > tmax){ return false; } else {
		Intersection inter;
		inter.dist = t;
		inter.normal = calcNormale(r0 + rd*t);
		inter.Objet = this;
		I = inter;
		return true;
	}
}

glm::vec3 RoundBoxRM::calcNormale(glm::vec3 pos){
	glm::vec3 v = glm::vec3(0.001, 0.0, 0.0);
	glm::vec3 normale = glm::vec3(
		map(pos + glm::vec3(v.x, v.y, v.y)) - map(pos - glm::vec3(v.x, v.y, v.y)),
		map(pos + glm::vec3(v.y, v.x, v.y)) - map(pos - glm::vec3(v.y, v.x, v.y)),
		map(pos + glm::vec3(v.y, v.y, v.x)) - map(pos - glm::vec3(v.y, v.y, v.x)));
	return glm::normalize(normale);
}

float RoundBoxRM::map(glm::vec3 x){
	return distRoundBox(x - position, dimension, rayon);
}

float RoundBoxRM::distRoundBox(glm::vec3 pos, glm::vec3 dim, float r){
	return glm::length(glm::max(glm::abs(pos) - dim, 0.0f)) - r;
}