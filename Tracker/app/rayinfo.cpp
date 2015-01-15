/*
 * rayinfo
 *
 *  Created on: 21.10.2014
 *      Author: akin
 */

#include "rayinfo.hpp"

RayInfo::RayInfo( const Ray& ray, float distance )
: Ray(ray)
, distance(distance)
, bounces(0)
{
}

RayInfo::RayInfo( const Ray& ray, int bounces )
: Ray(ray)
, distance(0.0f)
, bounces(bounces)
{
}

RayInfo::RayInfo( const Ray& ray , float distance , int bounces )
: Ray(ray)
, distance(distance)
, bounces(bounces)
{
}
