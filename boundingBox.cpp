#include "boundingBox.hpp"

BoundingBox::BoundingBox(glm::vec3 min, glm::vec3 max){
	assert(min < max);
	boundaries[0] = min;
	boundaries[1] = max;
}

bool BoundingBox::intersectionBoundingBox(Rayon &r, float t1, float t2){
	float xmin, xmax, ymin, ymax, zmin, zmax;
	if (r.Vect().x >= 0){
		xmin = (boundaries[0].x - r.Orig().x) / r.Vect().x;
		xmax = (boundaries[1].x - r.Orig().x) / r.Vect().x;
	}
	else{
		xmin = (boundaries[1].x - r.Orig().x) / r.Vect().x;
		xmax = (boundaries[0].x - r.Orig().x) / r.Vect().x;
	}
	if (r.Vect().y >= 0){
		ymin = (boundaries[0].y - r.Orig().y) / r.Vect().y;
		ymax = (boundaries[1].y - r.Orig().y) / r.Vect().y;
	}
	else{
		ymin = (boundaries[1].y - r.Orig().y) / r.Vect().y;
		ymax = (boundaries[0].y - r.Orig().y) / r.Vect().y;
	}

	if ((xmin > ymax) || (ymin > xmax)) { return false; }

	if (ymin > xmin){ xmin = ymin; }
	if (ymax > xmax){ xmax = ymax; }
	
	if (r.Vect().z >= 0){
		zmin = (boundaries[0].z - r.Orig().z) / r.Vect().z;
		zmax = (boundaries[1].z - r.Orig().z) / r.Vect().z;
	}
	else{
		zmin = (boundaries[1].z - r.Orig().z) / r.Vect().z;
		zmax = (boundaries[0].z - r.Orig().z) / r.Vect().z;
	}

	if ((xmin > zmax) || (zmin > xmax)) { return false; }

	if (zmin > xmin){ xmin = zmin; }
	if (zmax > xmax){ xmax = zmax; }

	return ((xmin < t2) && (xmax > t1));
}
