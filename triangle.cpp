#include "triangle.hpp"
#include "rayon.hpp"
#include "Intersection.hpp"
#include <glm/gtx/intersect.hpp>

Triangle::Triangle(){}

Triangle::~Triangle(){}

Triangle::Triangle(glm::vec3 a, glm::vec3 b, glm::vec3 c){
	V0 = a;
	V1 = b;
	V2 = c;
}


bool Triangle::calculIntersection(const Rayon &r, Intersection &I){
	//MINIMUM STORAGE RAY TRIANGLE INTERSECTION BY TRUMBORE AND MULLER
	/*glm::vec3 edge1, edge2, tvec, pvec, qvec;
	float det, inv_det;
	float u, v, t;
	Intersection inter;

	edge1 = V1 - V0;
	edge2 = V2 - V0;

	pvec = glm::cross(r.Vect(), edge2);

	det = glm::dot(edge1, pvec);



	//bool i = glm::intersectRayTriangle(r.Orig(), r.Vect(), V0, V1, V2, edge1);
	if (det < 0.000001){
		return false;
	}

	tvec = r.Orig() - V0;

	u = glm::dot(tvec, pvec);
	if (u < 0.0f || u > det){
		return false;
	}

	qvec = glm::cross(tvec, edge1);

	v = glm::dot(r.Vect(), qvec);
	if (v < 0.0f || u + v > det){
		return false;
	}

	t = glm::dot(edge2, qvec);
	inv_det = 1.0f / det;
	t *= inv_det;
	u *= inv_det;
	v *= inv_det;

	//Intersection inter;
	inter.dist = t;
	inter.Objet = this;
	inter.normal = glm::normalize(glm::cross(edge1, edge2));
	I = inter;
	
	


	if (det > -0.000001 && det < 0.000001){
		return false;
	}
	//inv_det = 1.0f / det;

	tvec = r.Orig() - V0;

	u = glm::dot(tvec, pvec) * inv_det;
	if (u < 0.0f || u > 1.0f){
		return false;
	}

	qvec = glm::cross(tvec, edge1);

	v = glm::dot(r.Vect(), qvec)*inv_det;
	if (v < 0.0f || u + v > 1.0f){
		return false;
	}

	t = glm::dot(edge2, qvec) * inv_det;
	//Intersection inter;
	inter.dist = t;
	inter.Objet = this;
	glm::vec3 normal = glm::cross(edge1, edge2);
	if (normal.z > 0){
		normal.z = -normal.z;
		inter.normal = glm::normalize(normal);
		I = inter;
		return true;
	}

	inter.normal = glm::normalize(normal);
	I = inter;
	
	return true;*/
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	/*
	glm::vec3 edge1 = V1 - V0;
	glm::vec3 edge2 = V2 - V0;
	glm::vec3 pvec = glm::cross(r.Vect(), edge2);
	float det = glm::dot(edge1, pvec);
	if (det == 0){ return false; }
	float invDet = 1.0f / det;
	glm::vec3 tvec = r.Orig() - V0;
	float u;
	if (det < 0){
		u = glm::dot(tvec, pvec) * invDet;
	}
	else{
		u = glm::dot(tvec, pvec);
	}
	
	if (u < 0 || u > 1.0f){ return false; }
	glm::vec3 qvec = glm::cross(tvec, edge1);
	float v = glm::dot(r.Orig(), qvec) * invDet;
	if (v < 0 || u + v > 1.0f){ return false; }
	float t = glm::dot(edge2, qvec) * invDet;

	Intersection inter;
	inter.dist = t;
	inter.Objet = this;
	glm::vec3 normale = glm::normalize(glm::cross(edge1, edge2));
	inter.normal = glm::normalize(glm::cross(edge2, edge1));
	if (inter.normal.z > 0){ inter.normal.z = -inter.normal.z; }
	I = inter;
	return true;*/
	////////////////////////////////////////////////////////////////////////////////////////////////////////////

	double det, invdet;
	glm::vec3 edge1 = V1 - V0;
	glm::vec3 edge2 = V2 - V0;

	/* Find the cross product of edge2 and the ray direction */
	glm::vec3 s1 = glm::cross(r.Vect(), edge2);

	det = glm::dot(edge1, s1);
	if (det > -0.000001 && det < 0.000001) {
		return false;
	}

	invdet = 1 / det;

	glm::vec3 s2 = r.Orig() - V0;

	double u = glm::dot(s2, s1) * invdet;

	if (u < 0 || u > 1) {
		return false;
	}

	glm::vec3 s3 = glm::cross(s2, edge1);

	double v = glm::dot(r.Vect(), s3) * invdet;

	if (v < 0 || (u + v) > 1) {
		return false;
	}

	double tmp = glm::dot(edge2, s3) * invdet;

	if (tmp < 0) {
		return false;
	}

	/* subtract tiny amount - otherwise artifacts due to floating point imprecisions... */
	float dist = tmp /*- 0.005*/;
	glm::vec3 normal = glm::normalize(glm::cross(edge2, edge1));
	Intersection inter;
	inter.dist = dist;
	inter.Objet = this;
	inter.normal = -normal;
	//if (inter.normal.z >= 0){ inter.normal.z = -inter.normal.z; }
	I = inter;
	return true;
}