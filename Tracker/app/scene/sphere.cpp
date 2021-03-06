/*
 * sphere.cpp
 *
 *  Created on: 22.10.2014
 *      Author: akin
 */

#include "sphere.hpp"
#include "../intersect.hpp"
#include <graphics/colortools.hpp>
#include "../hitinfo.hpp"

Sphere::Sphere()
: radius( 0.0f )
{
}

Sphere::~Sphere()
{
}

float Sphere::getEmissionRadius() const
{
	Color color;
	if( material.emission != nullptr)
	{
		material.emission->at(0.0f, color);
	}
	return radius + core::graphics::lightMaxDistance(color);
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
