#ifndef OCTREE_HPP
#define OCTREE_HPP

#include "boundingBox.hpp"

class Octree
{
public:
	Octree();
	Octree(BoundingBox* boiteEnglobante, std::vector<Objet3D*> );

	BoundingBox boiteEnglobante;
	std::vector <Objet3D*> listeObjets;
	Octree* parent;
	Octree* child = new Octree[8];
	int activeNode;
	int minimumSize = 1;
};

#endif //!OCTREE_HPP
//http://www.gamedev.net/page/resources/_/technical/game-programming/introduction-to-octrees-r3529