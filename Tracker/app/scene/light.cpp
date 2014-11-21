/*
 * light.cpp
 *
 *  Created on: 24.10.2014
 *      Author: akin
 */

#include "light"

Light::Light()
{
}

Light::~Light()
{
}

void Light::at( const glm::vec3& point , Color& intensity ) const
{
	glm::vec3 position;
	transform(position);
	
	intensity = this->intensity;
	lightAttenuation( glm::distance( position , point ) , intensity );
}
