/*
 * INTERSECT
 *
 *  Created on: 21.10.2014
 *      Author: akin
 */

#ifndef APP_INTERSECT_HPP_
#define APP_INTERSECT_HPP_

#include <core.hpp>
#include "ray.hpp"
#include "line.hpp"
#include "scene/node.hpp"

bool intersects( const Ray& ray , const glm::vec3& position , float radius );
bool intersects(
				const Ray& ray ,
				const glm::vec3& position ,
				float radius ,
				glm::vec3& hitpoint ,
				float& distance ,
				glm::vec3& normal ,
				float& inside );

bool intersects( const Ray& ray , const glm::vec3& position , const glm::vec3& normal , glm::vec3& hitpoint , float& distance );

//bool intersects( const glm::vec3& p1 , const glm::vec3& p2 , const Node& node );

#endif // APP_INTERSECT_HPP_
