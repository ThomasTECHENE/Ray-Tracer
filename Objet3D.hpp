

#ifndef OBJECT_HPP_
#define OBJECT_HPP_

#include <iostream>
#include "Intersection.hpp"
#include <vector>
#include "Material.hpp"

class Rayon;
class Objet3D
{
 protected:


  
 public:

	 Objet3D();
	 ~Objet3D();
     virtual bool calculIntersection(const Rayon &, Intersection &I){return false;};
	 Material* material;
};


#endif 
