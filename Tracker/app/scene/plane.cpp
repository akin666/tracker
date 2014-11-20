/*
 * Plane
 *
 *  Created on: 22.10.2014
 *      Author: akin
 */

#include "plane"
#include "../intersect"

Plane::Plane()
{
}

Plane::~Plane()
{
}

bool Plane::intersects( const Ray& ray , HitInfo& info ) const
{
	return false;
	/*
	bool hit = ::intersects( ray , getPosition() , radius , info.point , info.distance , info.normal );
	
	if(hit)
	{
		info.material = material;
	}
	return hit;
	*/
}
