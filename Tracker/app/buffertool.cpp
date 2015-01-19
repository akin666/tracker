/*
 * Buffertool.cpp
 *
 *  Created on: 23.10.2014
 *      Author: akin
 */

#include "buffertool.hpp"
#include <glm/glm.hpp>
#include "scene/world.hpp"
#include <graphics/colortools.hpp>

using namespace core;
using namespace core::graphics;

BufferTool::BufferTool()
{
}

BufferTool::~BufferTool()
{
}

void BufferTool::convert( const Buffer2D<Color>& source , Buffer2D<RGBALow>& target )
{
	target.init( source.width() , source.height() );
	
	auto *trg = target.buffer();
	const auto *src = source.buffer();
	
	size_t length = source.size();
	
	for( size_t i = 0 ; i < length ; ++i )
	{
		//pixelConvert(src[i], trg[i]);
		::convert(trg[i] , src[i]);
	}
}

void BufferTool::clear( Buffer2D<Color>& target )
{
	auto *trg = target.buffer();
	size_t length = target.size();
	
	for( size_t i = 0 ; i < length ; ++i )
	{
		trg[i] = World::clear;
	}
}

// http://stackoverflow.com/questions/9465815/rgb-to-yuv420-algorithm-efficiency
size_t rgb2Yuv420p( const Buffer2D<Color>& source , Buffer2D<YUVLow>& target )
{
	uint8_t *destination = (uint8_t*)target.buffer();
	const auto *src = source.buffer();
	
	size_t width = source.width();
	size_t height = source.height();
	
	size_t image_size = width * height;
	size_t upos = image_size;
	size_t vpos = upos + upos / 4;
	size_t i = 0;
	RGBALow color;
	
	for( size_t line = 0; line < height; ++line )
	{
		if( !(line % 2) )
		{
			for( size_t x = 0; x < width; x += 2 )
			{
				convert( color , src[i] );
				destination[i++] = ((66*color.r + 129*color.g + 25*color.b) >> 8) + 16;
				destination[upos++] = ((-38*color.r + -74*color.g + 112*color.b) >> 8) + 128;
				destination[vpos++] = ((112*color.r + -94*color.g + -18*color.b) >> 8) + 128;
				
				convert( color , src[i] );
				destination[i++] = ((66*color.r + 129*color.g + 25*color.b) >> 8) + 16;
			}
		}
		else
		{
			for( size_t x = 0; x < width; x += 1 )
			{
				convert( color , src[i] );
				destination[i++] = ((66*color.r + 129*color.g + 25*color.b) >> 8) + 16;
			}
		}
	}
	
	return vpos;
}

size_t BufferTool::convert( const Buffer2D<Color>& source , Buffer2D<YUVLow>& target )
{
	target.init( source.width() , source.height() );
	
	return rgb2Yuv420p(source , target);
	
	// TODO!
	// target.setUsed( used );
}
