/*
 * material.cpp
 *
 *  Created on: 24.10.2014
 *      Author: akin
 */

#include "material.hpp"

Material::Material()
{
}

Material::Material(const Material& other)
: reflection(other.reflection)
, emission(other.emission)
, transparency(other.transparency)
, diffuse(other.diffuse)
, refraction(other.refraction)
, name(other.name)
{
}

Material::~Material()
{
}
