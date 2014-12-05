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
	float distance = glm::distance( ray.position , pos );
	
	bool hit = ::intersects( ray , pos , radius , info.point , info.distance , info.normal );
	
	bool in = radius > distance;
	
	if( !hit && in )
	{
		int hh = 1;
	}
	
	bool hit2 = ::intersects( ray , pos , radius , info.point , info.distance , info.normal );
	
	
	if(hit)
	{
		info.material = material;
		info.inside = in ? 1.0f : -1.0f;
	}
	return hit;
}
