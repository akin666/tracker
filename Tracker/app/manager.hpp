/*
 * manager
 *
 *  Created on: 24.10.2014
 *      Author: akin
 */

#ifndef APP_MANAGER_HPP_
#define APP_MANAGER_HPP_

#include <core.hpp>
#include <graphics/sampler/sampler.hpp>
#include "material.hpp"

class Sampler;
class Manager
{
private:
	std::unordered_map<std::string, core::graphics::Sampler::Shared> samplers;
	std::unordered_map<std::string, Material> materials;
public:
	Manager();
	~Manager();

	void set( std::string key , const Material& material );
	void set( std::string key , core::graphics::Sampler::Shared& sampler );

	bool get( std::string key , Material& material ) const;
	bool get( std::string key , core::graphics::Sampler::Shared& sampler ) const;

	bool hasMaterial( std::string key ) const;
	bool hasSampler( std::string key ) const;
};

#endif // APP_MANAGER_HPP_
