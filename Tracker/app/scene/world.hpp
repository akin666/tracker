/*
 * world.hpp
 *
 *  Created on: 24.10.2014
 *      Author: akin
 */

#ifndef APP_WORLD_HPP_
#define APP_WORLD_HPP_

#include <core>

class World
{
public:
	static const glm::vec4 center;
	static const glm::vec4 up;
	static const glm::vec4 down;
	static const glm::vec4 right;
	static const glm::vec4 left;
	static const glm::vec4 forward;
	static const glm::vec4 backward;
	
	
	static const Color clear;
	
	static const Color white;
	static const Color black;
	static const Color grey;
	
	static const Color red;
	static const Color green;
	static const Color blue;
	
	static const Color teal;
	static const Color yellow;
	static const Color magenta;
};

#endif // APP_WORLD_HPP_
