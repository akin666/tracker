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

BufferTool::BufferTool()
{
}

BufferTool::~BufferTool()
{
}

void BufferTool::convert( const PixelBuffer<Color>& source , PixelBuffer<RGBALow>& target )
{
	target.init<Color>( source );
	
	auto *trg = target.getBuffer();
	const auto *src = source.getBuffer();
	
	size_t length = source.getSize();
	
	for( size_t i = 0 ; i < length ; ++i )
	{
		//pixelConvert(src[i], trg[i]);
		::convert(trg[i] , src[i]);
	}
}

void BufferTool::clear( PixelBuffer<Color>& target )
{
	auto *trg = target.getBuffer();
	size_t length = target.getSize();
	
	for( size_t i = 0 ; i < length ; ++i )
	{
		trg[i] = World::clear;
	}
}

// http://stackoverflow.com/questions/9465815/rgb-to-yuv420-algorithm-efficiency
size_t rgb2Yuv420p( const PixelBuffer<Color>& source , PixelBuffer<YUVLow>& target )
{
	uint8_t *destination = (uint8_t*)target.getBuffer();
	const auto *src = source.getBuffer();
	
	size_t width = source.getWidth();
	size_t height = source.getHeight();
	
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

void BufferTool::convert( const PixelBuffer<Color>& source , PixelBuffer<YUVLow>& target )
{
	target.init<Color>( source );
	
	size_t used = rgb2Yuv420p(source , target);
	
	target.setUsed( used );
}
