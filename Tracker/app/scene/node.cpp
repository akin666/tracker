/*
 * node.cpp
 *
 *  Created on: 28.10.2014
 *      Author: akin
 */

#include "node"
#include "../hitinfo"
#include "../materials"

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
	glm::vec4 pos(0.0f, 0.0f, 0.0f, 1.0f);
	
	pos = matrix * pos;
	
	return glm::vec3( pos.x , pos.y , pos.z );
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
