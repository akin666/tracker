/*
 * sphere.cpp
 *
 *  Created on: 22.10.2014
 *      Author: akin
 */

#include "sphere"
#include "../intersect"

Sphere::Sphere()
: radius( 0.0f )
{
}

Sphere::~Sphere()
{
}

bool Sphere::intersects( const Ray& ray , HitInfo& info ) const
{
	bool hit = ::intersects( ray , getPosition() , radius , info.point , info.distance , info.normal );
	
	if(hit)
	{
		info.material = material;
	}
	return hit;
}
