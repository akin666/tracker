/*
 * rootsolver.cpp
 *
 *  Created on: 28.10.2014
 *      Author: akin
 */

#include "solver"
#include "../scene/world"

namespace solver
{
	Color blank( const Scene& scene , const Ray& ray )
	{
		return World::black;
	}
}