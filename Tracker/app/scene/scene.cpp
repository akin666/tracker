/* 
 * File:   scene.cpp
 * Author: akin
 * 
 * Created on 20. lokakuuta 2014, 21:09
 */

#include "scene"

Scene::Scene()
{
	base.transparency.x = 1.0f;
	base.transparency.y = 1.0f;
	base.transparency.z = 1.0f;
}

Scene::~Scene()
{
	for( auto *node : nodes )
		delete node;
	for( auto *light : lights )
		delete light;
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
}

void Scene::add( Light *light )
{
	lights.push_back( light );
}

void Scene::add( Camera *camera )
{
	cameras.push_back( camera );
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
			}
		}
	}
}

const std::vector<Node*>& Scene::getNodes() const
{
	return nodes;
}

const std::vector<Light*>& Scene::getLights() const
{
	return lights;
}

const std::vector<Camera*>& Scene::getCameras() const
{
	return cameras;
}
