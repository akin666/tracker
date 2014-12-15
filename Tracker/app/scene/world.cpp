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

#define RGB_TO_COLOR
// #define RGB_TO_COLOR rgb2hsb

const Color World::clear = RGB_TO_COLOR( Color( 0.0f , 0.0f , 0.0f ) );

const Color World::white = RGB_TO_COLOR( Color( 1.0f , 1.0f , 1.0f ) );
const Color World::black = RGB_TO_COLOR( Color( 0.0f , 0.0f , 0.0f ) );
const Color World::grey = RGB_TO_COLOR( Color( 0.5f , 0.5f , 0.5f ) );

const Color World::red = RGB_TO_COLOR( Color( 1.0f , 0.0f , 0.0f ) );
const Color World::green = RGB_TO_COLOR( Color( 0.0f , 1.0f , 0.0f ) );
const Color World::blue = RGB_TO_COLOR( Color( 0.0f , 0.0f , 1.0f ) );

const Color World::teal = RGB_TO_COLOR( Color( 0.0f , 1.0f , 1.0f ) );
const Color World::yellow = RGB_TO_COLOR( Color( 1.0f , 1.0f , 0.0f ) );
const Color World::magenta = RGB_TO_COLOR( Color( 1.0f , 0.0f , 1.0f ) );