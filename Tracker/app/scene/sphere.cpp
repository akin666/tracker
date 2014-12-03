/*
 * sphere.cpp
 *
 *  Created on: 22.10.2014
 *      Author: akin
 */

#include "sphere"
#include "../intersect"
#include <colortools>
#include "../hitinfo"

Sphere::Sphere()
: radius( 0.0f )
{
}

Sphere::~Sphere()
{
}

float Sphere::getEmissionRadius() const
{
	return ::lightMaxDistance(material.emission);
}

const Material& Sphere::getMaterial() const
{
	return material;
}

bool Sphere::intersects( const Ray& ray , HitInfo& info ) const
{
	const auto& pos = getPosition();
	bool hit = ::intersects( ray , pos , radius , info.point , info.distance , info.normal );
	
	if(hit)
	{
		info.material = material;
		info.inside = radius < glm::distance( ray.position , pos ) ? 1.0f : -1.0f;
	}
	return hit;
}
