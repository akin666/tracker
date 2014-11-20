/*
 * rayinfo
 *
 *  Created on: 21.10.2014
 *      Author: akin
 */

#include "rayinfo"

RayInfo::RayInfo( const Material& material , const Ray& ray, float distance )
: Ray(ray)
, material(material)
, distance(distance)
, bounces(0)
{
}

RayInfo::RayInfo( const Material& material , const Ray& ray, int bounces )
: Ray(ray)
, material(material)
, distance(0.0f)
, bounces(bounces)
{
}

RayInfo::RayInfo( const Material& material , const Ray& ray , float distance , int bounces )
: Ray(ray)
, material(material)
, distance(distance)
, bounces(bounces)
{
}
