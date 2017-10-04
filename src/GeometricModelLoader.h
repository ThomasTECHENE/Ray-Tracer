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

#ifndef _GEOEMTRICAL_Node_LOADER_
#define _GEOEMTRICAL_Node_LOADER_

//#include "../Utils/Constants.h"
#include <string>
using namespace std;
class GeometricModel;

class GeometricModelLoader
{
	public:
		GeometricModelLoader(){};
		~GeometricModelLoader(){};
		virtual bool loadModel(string name,GeometricModel *model) = 0;

};
#endif
