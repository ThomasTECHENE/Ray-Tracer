/*
 *	(c) XLim, UMR-CNRS 7252 , 2011-2014
 *	Authors: G.Gilet,N.Pavie

 This file is part of GobLim.

    GobLim is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    GobLim is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with Foobar.  If not, see <http://www.gnu.org/licenses/>
 *
 *
 */

#include <iostream>
#include "GeometricModel.h"
#include "GeometricModelLoader.h"

using namespace std;


#ifdef USE_ASSIMP
#include "GeometricModelLoader/AssimpLoader.h"
GeometricModelLoader* GeometricModel::loader = new AssimpLoader();
#else
#include "OBJLoader.h"
GeometricModelLoader* GeometricModel::loader = new OBJLoader();
#endif


GeometricModel::GeometricModel()
{
	nb_vertex = 0;
	nb_faces = 0;
};
GeometricModel::GeometricModel(std::string name,bool loadnow)
{
	nb_vertex = 0;
	nb_faces = 0;
	m_Name = name;
	if (loadnow)
		loader->loadModel(name,this);
};
GeometricModel::~GeometricModel()
{

};
const std::string GeometricModel::getName()
{
	return m_Name;
}
