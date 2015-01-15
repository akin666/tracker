/*
 * tracer.cpp
 *
 *  Created on: 21.10.2014
 *      Author: akin
 */

#include "intersect.hpp"

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
	
	double t1 = (-b + d)/(a * 2.0);
	double t2 = (-b - d)/(a * 2.0);
	
	return t1 >= 0.0f || t2 >= 0.0f;
}

bool intersects(
				const Ray& ray ,
				const glm::vec3& position ,
				float radius ,
				glm::vec3& hitpoint ,
				float& distance ,
				glm::vec3& normal ,
				float& inside )
{
	glm::vec3 diff = ray.position - position;
	float length = glm::length( diff );
	
	inside = length - radius;
	
	double a = glm::dot(ray.direction , ray.direction);
	double b = 2.0f * glm::dot(ray.direction , diff);
	double c = glm::dot(diff , diff) - (radius * radius);
	double d = b * b - 4.0f * a * c;
	
	if(d < 0.0)
	{
		return false;
	}
	
	if( d == 0.0 )
	{
		// ONLY 1 hitpoint!
	}
	
	d = glm::sqrt( d );
	
	double t1 = (-b + d)/(a * 2.0);
	double t2 = (-b - d)/(a * 2.0);
	
	float t = (float)t1;
	if( t1 > t2 || t1 <= 0.0 )
	{
		t = (float)t2;
	}
	
	if( t <= 0.0 )
	{
		return false;
	}
	
	// calculate hit
	distance = glm::sqrt(a) * t;
	hitpoint = ray.position + t * ray.direction;
	normal = (hitpoint - position) / radius;
	
	return true;
}

bool intersects( const Ray& ray , const glm::vec3& position , const glm::vec3& normal , glm::vec3& hitpoint , float& distance )
{
	float dotn = glm::dot( ray.direction , normal );
	glm::vec3 diff = position - ray.position;
	
	// never happens.
	if( dotn == 0.0f )
	{
		return false;
	}
	
	float dist = glm::dot( diff , normal ) / dotn;
	if( dist < 0.0f )
	{
		return false;
	}
	
	distance = dist;
	hitpoint = ray.position + ( ray.direction * distance );
	
	return true;
}
