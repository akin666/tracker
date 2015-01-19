/*
 * camera.cpp
 *
 *  Created on: 24.10.2014
 *      Author: akin
 */

#include "camera.hpp"
#include "../buffertool.hpp"

Camera::Camera()
: distance( 0.1f )
{
	buffer = std::make_shared<core::graphics::Buffer2D<Color>>();
}

Camera::~Camera()
{
}

float Camera::getWidth() const
{
	return width * scale;
}

float Camera::getHeight() const
{
	return height * scale;
}

float Camera::getDistance() const
{
	return distance * scale;
}

float Camera::getDpmm() const
{
	return dpmm;
}

void Camera::init()
{
	// init buffer..
	buffer->init((uint)getWidth() , (uint)getHeight() );
	BufferTool::clear( *buffer );
}

core::graphics::Buffer2D<Color>::Shared Camera::getBuffer()
{
	return buffer;
}
