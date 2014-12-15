/*
 * node.cpp
 *
 *  Created on: 28.10.2014
 *      Author: akin
 */

#include "node"
#include "../hitinfo"
#include "world"
#include <glm/gtc/matrix_transform.hpp>
#include <glm/ext.hpp>

Node::Node()
{
}

Node::~Node()
{
}

float Node::getEmissionRadius() const
{
	return 0.0f;
}

bool Node::intersects( const Ray& ray , HitInfo& info ) const
{
	return false;
}

const Material& Node::getMaterial() const
{
	throw "NOOOO";
}

void Node::add( Node *child )
{
	childs.push_back(child);
}

void Node::traverse(const glm::mat4& parent)
{
	matrix = parent;
	traverseChilds();
}

void Node::traverseChilds()
{
	auto current = matrix * delta;
	
	for( auto *child : childs )
	{
		child->traverse(current);
	}
}

void Node::setPosition( float x , float y , float z )
{
	this->setPosition( glm::vec3(x,y,z) );
}

void Node::setPosition( glm::vec3 position )
{
	delta[3][0] = position.x;
	delta[3][1] = position.y;
	delta[3][2] = position.z;
	traverseChilds();
}

glm::vec3 Node::getPosition() const
{
	auto current = matrix * delta;
	glm::vec4 pos = current * World::center;
	return glm::vec3( pos.x , pos.y , pos.z );
}

glm::vec3 Node::getUp() const
{
	auto current = matrix * delta;
	glm::vec4 pos = current * World::up;
	return glm::vec3( pos.x , pos.y , pos.z );
}

glm::vec3 Node::getForward() const
{
	auto current = matrix * delta;
	glm::vec4 pos = current * World::forward;
	return glm::vec3( pos.x , pos.y , pos.z );
}

void Node::move( float x , float y , float z )
{
	move(glm::vec3(x,y,z));
}

void Node::move( const glm::vec3& amount )
{
	auto transmat = glm::translate( glm::mat4x4() , amount );
	delta = transmat * delta;
	traverseChilds();
}

void Node::rotate( float x , float y , float z )
{
	rotate(glm::vec3(x,y,z));
}

void Node::rotate( const glm::vec3& amount )
{
	auto arad = glm::radians( amount );
	auto rotmat = glm::eulerAngleYXZ(arad.y, arad.x, arad.z);
	delta = rotmat * delta;
	traverseChilds();
}

void Node::reset()
{
	delta = glm::mat4();
	traverseChilds();
}

void Node::transform( glm::vec3& point ) const
{
	glm::vec4 pos(point, 1.0f);
	
	auto current = matrix * delta;
	pos = current * pos;
	
	point.x = pos.x;
	point.y = pos.y;
	point.z = pos.z;
}

void Node::get( glm::mat4& out ) const
{
	out = matrix * delta;
}
