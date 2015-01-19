/*
 * material.hpp
 *
 *  Created on: 24.10.2014
 *      Author: akin
 */

#ifndef APP_MATERIAL_HPP_
#define APP_MATERIAL_HPP_

#include <core.hpp>
#include <graphics/sampler/sampler.hpp>

class Material
{
public:
	// Surface:
	core::graphics::Sampler::Shared reflection;
	core::graphics::Sampler::Sampler::Shared emission;
	core::graphics::Sampler::Sampler::Shared transparency; // 0.0 opaque, 1.0 transparent
	core::graphics::Sampler::Sampler::Shared normal;
	
	core::graphics::Sampler::Sampler::Shared diffuse;
	
	core::graphics::Sampler::Sampler::Shared refraction;
	
	std::string name;
public:
	Material();
	Material(const Material& other);
	~Material();
};

#endif // APP_MATERIAL_HPP_ 
