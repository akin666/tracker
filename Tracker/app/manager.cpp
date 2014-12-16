/*
 * manager.cpp
 *
 *  Created on: 24.10.2014
 *      Author: akin
 */

#include "manager"
#include "scene/world"
#include <colorsampler>

Manager::Manager()
{
	Sampler::Shared clear(new ColorSampler(World::clear));
	
	Sampler::Shared white(new ColorSampler(World::white));
	Sampler::Shared black(new ColorSampler(World::black));
	Sampler::Shared grey(new ColorSampler(World::grey));
	
	Sampler::Shared red(new ColorSampler(World::red));
	Sampler::Shared green(new ColorSampler(World::green));
	Sampler::Shared blue(new ColorSampler(World::blue));
	
	Sampler::Shared teal(new ColorSampler(World::teal));
	Sampler::Shared yellow(new ColorSampler(World::yellow));
	Sampler::Shared magenta(new ColorSampler(World::magenta));
	
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

void Manager::set( String key , const Material& material )
{
	materials[key] = material;
}

void Manager::set( String key , Sampler::Shared& sampler )
{
	auto iter = samplers.find( key );
	if( iter != samplers.end() )
	{
		// replace!
		throw "NOOO";
	}
	samplers[key] = sampler;
}

bool Manager::get( String key , Material& material ) const
{
	auto iter = materials.find( key );
	if( iter == materials.end() )
	{
		return false;
	}
	material = iter->second;
	return true;
}

bool Manager::get( String key , Sampler::Shared& sampler ) const
{
	auto iter = samplers.find( key );
	if( iter == samplers.end() )
	{
		return false;
	}
	sampler = iter->second;
	return true;
}

bool Manager::hasMaterial( String key ) const
{
	return materials.find( key ) != materials.end();
}

bool Manager::hasSampler( String key ) const
{
	return samplers.find( key ) != samplers.end();
}
