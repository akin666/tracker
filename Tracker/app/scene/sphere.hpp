/*
 * sphere.hpp
 *
 *  Created on: 22.10.2014
 *      Author: akin
 */

#ifndef APP_SPHERE_HPP_
#define APP_SPHERE_HPP_

#include <core>
#include "node.hpp"
#include "../material.hpp"

class Sphere : public Node
{
public:
	Sphere();
	virtual ~Sphere();
	
	virtual float getEmissionRadius() const;
	virtual const Material& getMaterial() const;
	
	virtual bool intersects( const Ray& ray , HitInfo& info ) const;

	float radius;
	Material material;
};

#endif // APP_SPHERE_HPP_
