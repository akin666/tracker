/* 
 * File:   scene.cpp
 * Author: akin
 * 
 * Created on 20. lokakuuta 2014, 21:09
 */

#include "scene"
#include "../hitinfo"
#include "node"
#include "camera"
#include <colorsampler>
#include "world"

Scene::Scene()
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
	
	base.transparency = clear;
}

Scene::~Scene()
{
	for( auto *node : nodes )
		delete node;
	for( auto *camera : cameras )
		delete camera;
	
	nodes.clear();
	lights.clear();
	cameras.clear();
}

const Material& Scene::getMaterialAt( const glm::vec3& position ) const
{
	return base;
}

void Scene::add( Node *node )
{
	nodes.push_back( node );
	
	if( node->getEmissionRadius() > 0.0f )
	{
		lights.push_back(node);
	}
}

void Scene::add( Camera *camera )
{
	cameras.push_back( camera );
}

void Scene::set( String key , const Material& material )
{
	materials[key] = material;
}

void Scene::set( String key , Sampler::Shared& sampler )
{
	auto iter = samplers.find( key );
	if( iter != samplers.end() )
	{
		// replace!
		throw "NOOO";
	}
	samplers[key] = sampler;
}

bool Scene::get( String key , Material& material ) const
{
	auto iter = materials.find( key );
	if( iter == materials.end() )
	{
		return false;
	}
	material = iter->second;
	return true;
}

bool Scene::get( String key , Sampler::Shared& sampler ) const
{
	auto iter = samplers.find( key );
	if( iter == samplers.end() )
	{
		return false;
	}
	sampler = iter->second;
	return true;
}

bool Scene::hasMaterial( String key ) const
{
	return materials.find( key ) != materials.end();
}

bool Scene::hasSampler( String key ) const
{
	return samplers.find( key ) != samplers.end();
}

void Scene::setMaterial( const Material& material )
{
	base = material;
}

void Scene::getLights( const HitInfo& info , std::vector<Node*>& lights ) const
{
	lights = this->lights;
}

void Scene::trace( const Ray& ray , HitInfo& info ) const
{
	info.count = 0;
	info.distance = infinite;
	
	info.material = base;
	
	HitInfo tmp;
	for( auto *node : nodes )
	{
		if( node->intersects( ray , tmp ) )
		{
			++info.count;
			if( tmp.distance < info.distance )
			{
				info.distance = tmp.distance;
				info.point = tmp.point;
				info.normal = tmp.normal;
				info.inside = tmp.inside;
				
				info.node = node;
			}
		}
	}
	
	if( info.count > 0 )
	{
		if( info.inside >= 0.0f )
		{
			info.material = info.node->getMaterial();
		}
	}
}

void Scene::traceTo( const glm::vec3& position , const Node *target , HitInfo& info ) const
{
	info.count = 0;
	info.distance = infinite;
	
	info.material = base;
	
	Ray ray( position , glm::normalize( target->getPosition() - position ) );
	
	HitInfo tmp;
	for( auto *node : nodes )
	{
		// skip target
		if( target == node )
		{
			continue;
		}
		if( node->intersects( ray , tmp ) )
		{
			++info.count;
			if( tmp.distance < info.distance )
			{
				info.distance = tmp.distance;
				info.point = tmp.point;
				info.normal = tmp.normal;
				info.inside = tmp.inside;
				
				info.node = node;
			}
		}
	}
	
	if( info.count > 0 )
	{
		if( info.inside >= 0.0f )
		{
			info.material = info.node->getMaterial();
		}
	}
}

std::vector<Camera*>& Scene::getCameras()
{
	return cameras;
}
