#include "Octree.hpp"

Octree::Octree(BoundingBox* boiteEnglobante, std::vector<Objet3D*> listObj){

	this->boiteEnglobante = *boiteEnglobante;
	listeObjets = listObj;
}