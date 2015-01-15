/*
 * camera.hpp
 *
 *  Created on: 24.10.2014
 *      Author: akin
 */

#ifndef APP_CAMERA_HPP_
#define APP_CAMERA_HPP_

#include <core.hpp>
#include "node.hpp"
#include <graphics/buffer2d.hpp>

class Camera : public Node
{
private:
	PixelBuffer<Color> buffer;
public:
	Camera();
	virtual ~Camera();
	
	float distance;
	float width;
	float height;
	float dpmm;
	
	float scale;
	
	float getWidth() const;
	float getHeight() const;
	float getDistance() const;
	float getDpmm() const;
	
	void init();
	PixelBuffer<Color>& getBuffer();
};

#endif // APP_CAMERA_HPP_
