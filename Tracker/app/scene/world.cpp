/*
 * world.cpp
 *
 *  Created on: 24.10.2014
 *      Author: akin
 */

#include "world"

const glm::vec4 World::center( 0.0f , 0.0f , 0.0f , 1.0f );
const glm::vec4 World::up( 0.0f , 1.0f , 0.0f , 1.0f );
const glm::vec4 World::down( 0.0f , -1.0f , 0.0f , 1.0f );
const glm::vec4 World::left(-1.0f , 0.0f , 0.0f , 1.0f );
const glm::vec4 World::right( 1.0f , 0.0f , 0.0f , 1.0f );
const glm::vec4 World::forward( 0.0f , 0.0f , 1.0f , 1.0f );
const glm::vec4 World::backward( 0.0f , 0.0f ,-1.0f , 1.0f );
