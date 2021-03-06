/*
 * disc
 *
 *  Created on: 22.10.2014
 *      Author: akin
 *
 * Disc is a bit perverse thing, it is infinitely thin thing,
 * but at least it is not a plane, that has more infinites than
 * disc.
 *
 */

#ifndef APP_DISC_HPP_
#define APP_DISC_HPP_

#include <core.hpp>
#include "node.hpp"
#include "../material.hpp"

class Disc : public Node
{
public:
	Disc();
	virtual ~Disc();
	
	virtual float getEmissionRadius() const;
	virtual const Material& getMaterial() const;
	
	virtual bool intersects( const Ray& ray , HitInfo& info ) const;

	float radius;
	Material material;
};

#endif // APP_DISC_HPP_
