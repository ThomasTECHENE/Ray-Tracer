#include "Scene.hpp"



Scene::Scene()
{
}
Scene::~Scene()
{
	
}

void Scene::ajouterObjet(Objet3D *o)
{
	listObjets.push_back(o);
}