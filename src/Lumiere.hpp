#ifndef LUMIERE_HPP
#define LUMIERE_HPP

#include "glm/glm.hpp"

class Lumiere{
public:
	glm::vec3 position;

	void setPosition(glm::vec3 p);
};
#endif // !LUMIERE_HPP