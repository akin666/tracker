/*
 * manager.cpp
 *
 *  Created on: 24.10.2014
 *      Author: akin
 */

#include "manager.hpp"
#include "scene/world.hpp"
#include <graphics/sampler/color.hpp>

Manager::Manager()
{
	Sampler::Shared clear(new SamplerColor(World::clear));
	
	Sampler::Shared white(new SamplerColor(World::white));
	Sampler::Shared black(new SamplerColor(World::black));
	Sampler::Shared grey(new SamplerColor(World::grey));
	
	Sampler::Shared red(new SamplerColor(World::red));
	Sampler::Shared green(new SamplerColor(World::green));
	Sampler::Shared blue(new SamplerColor(World::blue));
	
	Sampler::Shared teal(new SamplerColor(World::teal));
	Sampler::Shared yellow(new SamplerColor(World::yellow));
	Sampler::Shared magenta(new SamplerColor(World::magenta));
	
	// Add basic samplers..
	set("clear" , clear);
	
	set("white" , white);
	set("black" , black);
	set("grey" , grey);
	
	set("red" , red);
	set("green" , green);
	set("blue" , blue);
	
	set("teal" , teal);
	set("yellow" , yellow);
	set("magenta" , magenta);
}

Manager::~Manager()
{
}

void Manager::set( std::string key , const Material& material )
{
	materials[key] = material;
}

void Manager::set( std::string key , Sampler::Shared& sampler )
{
	auto iter = samplers.find( key );
	if( iter != samplers.end() )
	{
		// replace!
		throw "NOOO";
	}
	samplers[key] = sampler;
}

bool Manager::get( std::string key , Material& material ) const
{
	auto iter = materials.find( key );
	if( iter == materials.end() )
	{
		return false;
	}
	material = iter->second;
	return true;
}

bool Manager::get( std::string key , Sampler::Shared& sampler ) const
{
	auto iter = samplers.find( key );
	if( iter == samplers.end() )
	{
		return false;
	}
	sampler = iter->second;
	return true;
}

bool Manager::hasMaterial( std::string key ) const
{
	return materials.find( key ) != materials.end();
}

bool Manager::hasSampler( std::string key ) const
{
	return samplers.find( key ) != samplers.end();
}
