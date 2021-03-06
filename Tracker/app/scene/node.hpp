/*
 * node.hpp
 *
 *  Created on: 28.10.2014
 *      Author: akin
 */

#ifndef APP_NODE_HPP_
#define APP_NODE_HPP_

#include <core.hpp>
#include <ray.hpp>
#include "../material.hpp"

using namespace core;

class HitInfo;
class Node
{
private:
	std::vector<Node*> childs;
protected:
	glm::mat4 delta;
	glm::mat4 matrix;
	
	void traverseChilds();
public:
	std::string name;
public:
	Node();
	virtual ~Node();
	
	virtual float getEmissionRadius() const;
	virtual bool intersects( const Ray& ray , HitInfo& info ) const;
	virtual const Material& getMaterial() const;
	
	void add( Node *child );
	void traverse(const glm::mat4& parent);
	
	void setPosition( float x , float y , float z );
	void setPosition( glm::vec3 position );
	
	glm::vec3 getPosition() const;
	glm::vec3 getUp() const;
	glm::vec3 getForward() const;
	
	void move( float x , float y , float z );
	void move( const glm::vec3& amount );
	
	void rotate( float x , float y , float z );
	void rotate( const glm::vec3& amount );
	
	void reset();
	
	void transform( glm::vec3& point ) const;
	virtual void get( glm::mat4& out ) const;
};

#endif // APP_NODE_HPP_
