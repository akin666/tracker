/*
 * pixelformat.cpp
 *
 *  Created on: 21.10.2014
 *      Author: akin
 */

#include "pixelformat"

namespace pixelformat
{

size_t getElementSize( Channels channels )
{
	size_t size = 0;
	for( unsigned int mask = 1 ; mask <= CHANNEL_MAX ; mask <<= 1 )
	{
		if( channels & mask ) ++size;
	}
	return size;
}

size_t getByteSize( Format format )
{
	switch( format )
	{
		case RGB8 		: return 3;
		case RGBA8 		: return 4;
		case ARGB8 		: return 4;
		case ALPHA8 	: return 1;
		case LUMINANCE8 : return 1;
		case INTENSITY8 : return 1;
		case RGBA12 	: return 6;
		case RGBA16 	: return 8;
		case RGBA32 	: return 16;
		case RGBA32F 	: return 16;
		case RGBA64F 	: return 32;
		case DEPTH8 	: return 1;
		case DEPTH16 	: return 2;
		case DEPTH24 	: return 3;
		case DEPTH32 	: return 4;
		case RGB565		: return 2;
		case RGBA4		: return 2;
		case RGBA5551	: return 2;
		default			: return 0;
	}
	return 0;
}

}
