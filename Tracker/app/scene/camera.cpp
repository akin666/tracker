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
	buffer.init((uint)getWidth() , (uint)getHeight() );
	BufferTool::clear( buffer );
}

PixelBuffer<Color>& Camera::getBuffer()
{
	return buffer;
}
