#include "coneRM.hpp"
#include "Intersection.hpp"
#include "rayon.hpp"

ConeRM::ConeRM(glm::vec3 pos, glm::vec3 dim){
	position = pos;
	dimension = dim;
}

bool ConeRM::calculIntersection(const Rayon &r, Intersection &I){
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

glm::vec3 ConeRM::calcNormale(glm::vec3 pos){
	glm::vec3 v = glm::vec3(0.001, 0.0, 0.0);
	glm::vec3 normale = glm::vec3(
		map(pos + glm::vec3(v.x, v.y, v.y)) - map(pos - glm::vec3(v.x, v.y, v.y)),
		map(pos + glm::vec3(v.y, v.x, v.y)) - map(pos - glm::vec3(v.y, v.x, v.y)),
		map(pos + glm::vec3(v.y, v.y, v.x)) - map(pos - glm::vec3(v.y, v.y, v.x)));
	return glm::normalize(normale);
}

float ConeRM::map(glm::vec3 x){
	return distCone(x - position, dimension);
}

float ConeRM::distCone(glm::vec3 p, glm::vec3 c)
{
	glm::vec2 p2 = glm::vec2(p.x, p.z);
	glm::vec2 c2 = glm::vec2(c.x, c.y);

	glm::vec2 q = glm::vec2(glm::length(p2), p.y);

	float d1 = -p.y - c.z;
	float d2 = glm::max(glm::dot(q, c2), p.y);
	return glm::length(glm::max(glm::vec2(d1, d2), 0.0f)) + glm::min(glm::max(d1, d2), 0.0f);
}