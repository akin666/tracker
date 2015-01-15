/* 
 * File:   scene.cpp
 * Author: akin
 * 
 * Created on 20. lokakuuta 2014, 21:09
 */

#include "scene.hpp"
#include "../hitinfo.hpp"
#include "node.hpp"
#include "camera.hpp"
#include "../manager.hpp"

Scene::Scene()
{
	manager.get("clear" , base.transparency);
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

Manager& Scene::getManager()
{
	return manager;
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
		
		info.materialCoordinates = (info.point - info.node->getPosition()) * 100.0f;
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
