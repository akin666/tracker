/*
 * tracer.cpp
 *
 *  Created on: 21.10.2014
 *      Author: akin
 */

#include "intersect"

// based on http://ray-tracer-concept.blogspot.fi/2011/11/ray-sphere-intersection.html
bool intersects( const Ray& ray , const glm::vec3& position , float radius )
{
	glm::vec3 diff = ray.position - position;
	
	float a = glm::dot(ray.direction , ray.direction);
	float b = 2.0f * glm::dot(ray.direction , diff);
	float c = glm::dot(diff , diff) - (radius * radius);
	float d = b * b - 4.0f * a * c;
	
	if(d < 0.0f)
	{
		return false;
	}
	d = glm::sqrt(d);
	float t = (-0.5f)*(b+d)/a;
	return t >= 0.0f;
}

// additions from http://sci.tuomastonteri.fi/programming/sse/example3
bool intersects( const Ray& ray , const glm::vec3& position , float radius , glm::vec3& hitpoint , float& distance , glm::vec3& normal )
{
	glm::vec3 diff = ray.position - position;
	
	float a = glm::dot(ray.direction , ray.direction);
	float b = 2.0f * glm::dot(ray.direction , diff);
	float c = glm::dot(diff , diff) - (radius * radius);
	float d = b * b - 4.0f * a * c;
	
	if(d < 0.0f)
	{
		return false;
	}
	d = glm::sqrt(d);
	float t = (-0.5f)*(b+d)/a;
	
	if( t < 0.0f )
	{
		return false;
	}
	
	// calculate hit
	distance = glm::sqrt(a) * t;
	hitpoint = ray.position + t * ray.direction;
	normal = (hitpoint - position) / radius;
	
	return true;
}

/*
bool intersects( const glm::vec3& p1 , const glm::vec3& p2 , const Node& node )
{
	// 3 points, p1,p2,p3
	const glm::vec3& p3 = node.getPosition();
	
	glm::vec3 d = p2 - p1;
	
	float a = glm::dot( d , d );
	float b = 2.0f * glm::dot( d , p1 - p3 );
	float c = glm::dot( p3 , p3 ) + glm::dot( p1 , p1 ) - 2.0f * glm::dot( p3 , p1 ) - node.radius * node.radius;
	
	return b*b - 4.0f * a * c >= 0.0f;
}
*/
