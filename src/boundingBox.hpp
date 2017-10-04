#ifndef BOUNDINGBOX_HPP
#define BOUNDINGBOX_HPP

#include "rayon.hpp"

class BoundingBox
{
public:
	//~BoundingBox(){};
	BoundingBox(){};
	BoundingBox(glm::vec3 min, glm::vec3 max);
	bool intersectionBoundingBox(Rayon &, float, float);

	glm::vec3 boundaries[2];

};

#endif //!BOUNDINGBOX_HPP