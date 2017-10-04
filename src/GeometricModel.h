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

#ifndef _GEOMETRIC_MODEL_H
#define _GEOMETRIC_MODEL_H

#include <glm/glm.hpp>
#include <vector>

#include "GeometricModelLoader.h"

struct Face
{
	int s1,s2,s3;
};

class GeometricModel
{
	public:
		GeometricModel();
		GeometricModel(std::string name,bool loadnow = true);
		~GeometricModel();

		const std::string getName();

		int nb_vertex;
		int nb_faces;

		std::vector < glm::vec3 > listVertex;
		std::vector <Face> listFaces;
		std::vector <Face> listCoordFaces;
		std::vector <glm::vec3> listNormals;
		std::vector < glm::vec3 > listCoords;
		std::vector < glm::vec4 > listTangents;


		static GeometricModelLoader* loader;


	protected:
		std::string m_Name;


};


#endif
