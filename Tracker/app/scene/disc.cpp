/*
 * disc
 *
 *  Created on: 22.10.2014
 *      Author: akin
 */

#include "disc"
#include "../intersect"
#include <colortools>
#include "../hitinfo"

Disc::Disc()
: radius( 0.0f )
{
}

Disc::~Disc()
{
}

float Disc::getEmissionRadius() const
{
	return radius + ::lightMaxDistance(material.emission);
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
