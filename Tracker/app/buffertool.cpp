/*
 * Buffertool.cpp
 *
 *  Created on: 23.10.2014
 *      Author: akin
 */

#include "buffertool"
#include <glm/glm.hpp>
#include "colors"

BufferTool::BufferTool()
{
}

BufferTool::~BufferTool()
{
}

inline void pixelConvertHSB( const Color& from , RGBALow& to )
{
	Color rgb;
	
	hsb2rgb(from, rgb);
	
	to.r = rgb.r < 1.0f ? (uint8)glm::floor(rgb.r * 0xFF) : 0xFF;
	to.g = rgb.g < 1.0f ? (uint8)glm::floor(rgb.g * 0xFF) : 0xFF;
	to.b = rgb.b < 1.0f ? (uint8)glm::floor(rgb.b * 0xFF) : 0xFF;
	to.a = 0xFF;
}

inline void pixelConvert( const Color& rgb , RGBALow& to )
{	
	to.r = rgb.r < 1.0f ? (uint8)glm::floor(rgb.r * 0xFF) : 0xFF;
	to.g = rgb.g < 1.0f ? (uint8)glm::floor(rgb.g * 0xFF) : 0xFF;
	to.b = rgb.b < 1.0f ? (uint8)glm::floor(rgb.b * 0xFF) : 0xFF;
	to.a = 0xFF;
}

void BufferTool::convertHSB( const PixelBuffer<Color>& source , PixelBuffer<RGBALow>& target )
{
	target.init<Color>( source );
	
	auto *trg = target.getBuffer();
	const auto *src = source.getBuffer();
	
	size_t length = source.getSize();
	
	for( size_t i = 0 ; i < length ; ++i )
	{
		pixelConvertHSB(src[i], trg[i]);
	}
}

void BufferTool::convert( const PixelBuffer<Color>& source , PixelBuffer<RGBALow>& target )
{
	target.init<Color>( source );
	
	auto *trg = target.getBuffer();
	const auto *src = source.getBuffer();
	
	size_t length = source.getSize();
	
	for( size_t i = 0 ; i < length ; ++i )
	{
		pixelConvert(src[i], trg[i]);
	}
}

void BufferTool::clear( PixelBuffer<Color>& target )
{
	auto *trg = target.getBuffer();
	size_t length = target.getSize();
	
	for( size_t i = 0 ; i < length ; ++i )
	{
		trg[i] = COLORS->clear;
	}
}
