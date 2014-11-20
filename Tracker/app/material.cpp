/*
 * material.cpp
 *
 *  Created on: 24.10.2014
 *      Author: akin
 */

#include "material"

Material::Material()
{
}

Material::Material(const Material& other)
: reflection(other.reflection)
, emission(other.emission)
, transparency(other.transparency)
, diffuse(other.diffuse)
, specular(other.specular)
, refraction(other.refraction)
, name(other.name)
{
}

Material::~Material()
{
}
