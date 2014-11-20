/*
 * commonnative.cpp
 *
 *  Created on: 16.6.2012
 *      Author: akin
 */

#include "../native"

#ifdef USE_COMMON_NATIVELIB

#include <iostream>
#include "tgalib.hpp"

namespace native {

void log( const std::string& hint , std::string message )
{
	std::cout << hint << " : " << message << std::endl;
}
	
std::string getPath( std::string location )
{
	if( location.empty() )
	{
		return "";
	}
	else if(location == "temporary" ||
			location == "temp" ||
			location == "tmp" )
	{
		return "tmp/";
	}
	return "unknown/";
}

bool saveImage(
    std::string location ,
	std::string name ,
	int width ,
	int height ,
	pixelformat::Format inputformat ,
	const void *pixels )
{
	std::string filename = getPath( location ) + name + ".tga";
	
	switch( inputformat )
	{
		case pixelformat::RGB8 :
			return tgalib::RGB8InterleavedWrite( filename , width , height , pixels );
			break;
		case pixelformat::RGBA8 :
			return tgalib::RGBA8InterleavedWrite( filename , width , height , pixels );
			break;
		case pixelformat::ALPHA8 :
			return tgalib::ALPHA8Write( filename , width , height , pixels );
			break;
		default:
			break;
	}
	return false;
}
	
unsigned int openVideo(
    std::string location ,
	std::string name ,
	int width ,
	int height ,
	pixelformat::Format inputformat ,
	int dpi ,
	int framerate )
{
	// filename to contain
	// [NAME]_ENC_[WIDTH]x[HEIGHT]_[DPI]_[PIXELFORMAT]_fr[FRAMERATE].video
	const int maxbuffer = 512;
	char buffer[ maxbuffer ];
	snprintf( buffer, (maxbuffer - 1), "%s_ENC_%dx%d_%d_%d_fr%d.video" , name.c_str() , width , height , dpi , inputformat , framerate );
	
	std::string path = getPath( location ) + std::string(buffer);
	
	return 0;
}
	
bool appendVideo( unsigned int handle , const void *pixels )
{
	return true;
}
	
bool closeVideo( unsigned int handle )
{
	return true;
}

} // native

#endif // USE_COMMON_NATIVE

