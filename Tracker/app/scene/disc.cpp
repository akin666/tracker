/*
 * disc
 *
 *  Created on: 22.10.2014
 *      Author: akin
 */

#include "disc.hpp"
#include "../intersect.hpp"
#include <graphics/colortools.hpp>
#include "../hitinfo.hpp"

Disc::Disc()
: radius( 0.0f )
{
}

Disc::~Disc()
{
}

float Disc::getEmissionRadius() const
{
	Color color;
	if( material.emission != nullptr)
	{
		material.emission->at(0.0f, color);
	}
	return radius + core::graphics::lightMaxDistance(color);
}

const Material& Disc::getMaterial() const
{
	return material;
}

bool Disc::intersects( const Ray& ray , HitInfo& info ) const
{
	const auto& pos = getPosition();
	const auto& normal = getUp();
	
	glm::vec3 hitpoint;
	float distance;
	
	if( ::intersects( ray , pos , normal , hitpoint , distance ) )
	{
		float discd = glm::distance( pos , hitpoint );
		if( discd <= radius )
		{
			info.point = hitpoint;
			info.normal = normal;
			info.distance = distance;
			info.inside = 1.0;
			return true;
		}
	}
	
	return false;
}
