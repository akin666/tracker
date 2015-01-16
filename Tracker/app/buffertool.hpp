/*
 * buffertool.hpp
 *
 *  Created on: 23.10.2014
 *      Author: akin
 */

#ifndef APP_BUFFERTOOL_HPP_
#define APP_BUFFERTOOL_HPP_

#include <graphics/buffer2d.hpp>
#include <core.hpp>

class BufferTool
{
public:
	BufferTool();
	~BufferTool();
	
	static void convert( const core::graphics::Buffer2D<core::graphics::Color>& source , core::graphics::Buffer2D<core::graphics::RGBALow>& target );
	static void convert( const core::graphics::Buffer2D<core::graphics::Color>& source , core::graphics::Buffer2D<core::graphics::YUVLow>& target );
	
	static void clear( core::graphics::Buffer2D<core::graphics::Color>& buffer );
};

#endif // APP_BUFFERTOOL_HPP_
