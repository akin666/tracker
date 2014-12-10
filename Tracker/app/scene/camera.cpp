/*
 * camera.cpp
 *
 *  Created on: 24.10.2014
 *      Author: akin
 */

#include "camera"

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
