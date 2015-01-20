/*
 * rayinfo
 *
 *  Created on: 21.10.2014
 *      Author: akin
 */

#ifndef APP_RAYINFO_HPP_
#define APP_RAYINFO_HPP_

#include <core.hpp>
#include <ray.hpp>

class RayInfo : public core::Ray
{
public:
	float distance;
	int bounces;
public:
	RayInfo( const core::Ray& ray , float distance = 0.0f );
	RayInfo( const core::Ray& ray , int bounces );
	RayInfo( const core::Ray& ray , float distance , int bounces );
};

#endif // APP_RAYINFO_HPP_
