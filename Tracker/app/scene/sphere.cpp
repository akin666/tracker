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
	
	bool hit = ::intersects( ray , pos , radius , info.point , info.distance , info.normal , info.inside );
	
	return hit;
}
