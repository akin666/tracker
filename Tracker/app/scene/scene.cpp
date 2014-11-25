/* 
 * File:   scene.cpp
 * Author: akin
 * 
 * Created on 20. lokakuuta 2014, 21:09
 */

#include "scene"
#include "../materials"

Scene::Scene()
{
	base.transparency.x = 0.0f;
	base.transparency.y = 0.0f;
	base.transparency.z = 0.0f;
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
	return MATERIALS->get( "air" );
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


void Scene::getLights( const HitInfo& info , std::vector<Node*>& lights ) const
{
	lights = this->lights;
}

void Scene::trace( const Ray& ray , HitInfo& info ) const
{
	info.count = 0;
	info.distance = infinite;
	
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
				info.material = tmp.material;
				info.inside = tmp.inside;
				info.node = node;
			}
		}
	}
}

void Scene::traceTo( const glm::vec3& position , const Node *target , HitInfo& info ) const
{
	info.count = 0;
	info.distance = infinite;
	
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
				info.material = tmp.material;
				info.inside = tmp.inside;
				info.node = node;
			}
		}
	}
}

const std::vector<Camera*>& Scene::getCameras() const
{
	return cameras;
}
