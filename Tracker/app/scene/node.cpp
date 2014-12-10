/*
 * node.cpp
 *
 *  Created on: 28.10.2014
 *      Author: akin
 */

#include "node"
#include "../hitinfo"
#include "../materials"
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
	return Materials::clear;
}

void Node::setPosition( float x , float y , float z )
{
	this->setPosition( glm::vec3(x,y,z) );
}

void Node::setPosition( glm::vec3 position )
{
	matrix[3][0] = position.x;
	matrix[3][1] = position.y;
	matrix[3][2] = position.z;
}

glm::vec3 Node::getPosition() const
{
	glm::vec4 pos = matrix * World::center;
	return glm::vec3( pos.x , pos.y , pos.z );
}

glm::vec3 Node::getUp() const
{
	glm::vec4 pos = matrix * World::up;
	return glm::vec3( pos.x , pos.y , pos.z );
}

glm::vec3 Node::getForward() const
{
	glm::vec4 pos = matrix * World::forward;
	return glm::vec3( pos.x , pos.y , pos.z );
}

void Node::move( float x , float y , float z )
{
	move(glm::vec3(x,y,z));
}

void Node::move( const glm::vec3& amount )
{
	auto transmat = glm::translate( glm::mat4x4() , amount );
	matrix = transmat * matrix;
}

void Node::rotate( float x , float y , float z )
{
	rotate(glm::vec3(x,y,z));
}

void Node::rotate( const glm::vec3& amount )
{
	auto arad = glm::radians( amount );
	auto rotmat = glm::eulerAngleYXZ(arad.y, arad.x, arad.z);
	
	matrix = rotmat * matrix;
}

void Node::reset()
{
	matrix = glm::mat4x4();
}

void Node::transform( glm::vec3& point ) const
{
	glm::vec4 pos(point, 1.0f);
	
	pos = matrix * pos;
	
	point.x = pos.x;
	point.y = pos.y;
	point.z = pos.z;
}

const glm::mat4& Node::getMatrix() const
{
	return matrix;
}
