#ifndef SCENE_HPP
#define SCENE_HPP

#include "Objet3D.hpp"
#include <vector>
#include "Lumiere.hpp"
class Scene
{
public:
	Scene();
	~Scene();
	Lumiere light, light2;
	void ajouterObjet(Objet3D *o);


	// Contient les elements de la scene
	std::vector < Objet3D*> listObjets;
	
};


#endif