/*
 * hitinfo
 *
 *  Created on: 21.10.2014
 *      Author: akin
 */

#ifndef APP_HITINFO_HPP_
#define APP_HITINFO_HPP_

#include <core.hpp>
#include "material.hpp"

class Node;
class HitInfo
{
public:
	float distance;
	glm::vec3 point;
	glm::vec3 normal;
	glm::vec3 materialCoordinates;
	Material material;
	float inside;
	Node *node;
	int count;
public:
	HitInfo();
};

#endif // APP_HITINFO_HPP_
