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

const glm::mat4& Camera::getMatrix() const
{
	return matrix; //glm::inverse(matrix);
}