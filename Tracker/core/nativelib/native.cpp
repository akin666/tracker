/*
 * commonnative.cpp
 *
 *  Created on: 16.6.2012
 *      Author: akin
 */

#include "../native"

#ifdef USE_COMMON_NATIVELIB

#include <iostream>
#include <fstream>

#define STB_IMAGE_WRITE_IMPLEMENTATION
#include <stb/stb_image_write.h>

#define STB_IMAGE_IMPLEMENTATION
#include <stb/stb_image.h>

namespace native {

void log( const String& hint , String message )
{
	std::cout << hint << " : " << message << std::endl;
}
	
String getPath( String location )
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
	
bool load( String path , String& content )
{
	std::ifstream file(path, std::ios::in | std::ios::binary);
	if( file )
	{
		file.seekg(0, std::ios::end);
		size_t size = file.tellg();
		content.resize(size);
		file.seekg(0, std::ios::beg);
		file.read(&content[0], size);
	
		return true;
	}
	return false;
}
/*
bool save( String location , String name , String& content )
{
	String filename = getPath( location ) + name;
	
	std::ifstream file(filename, std::ios::in | std::ios::binary);
	if( file )
	{
		file.seekg(0, std::ios::end);
		size_t size = file.tellg();
		content.resize(size);
		file.seekg(0, std::ios::beg);
		file.read(&content[0], size);
		
		return true;
	}
	return false;
}
*/
/*
bool saveImage(
    String location ,
	String name ,
	int width ,
	int height ,
	pixelformat::Format inputformat ,
	const void *pixels )
{
	String filename = getPath( location ) + name + ".png";
	
	switch( inputformat )
	{
		case pixelformat::RGB8 :
			return stbi_write_png(filename.c_str(), width, height, 3, pixels, 0) == 1;
			break;
		case pixelformat::RGBA8 :
			return stbi_write_png(filename.c_str(), width, height, 4, pixels, 0) == 1;
			break;
		case pixelformat::ALPHA8 :
			return stbi_write_png(filename.c_str(), width, height, 1, pixels, 0) == 1;
			break;
		default:
			break;
	}
	return false;
}*/

template <> bool load( String path , PixelBuffer<RGBALow>& buffer )
{
	int x,y,comp,req;
	req = 4;
	void *data = stbi_load( path.c_str() , &x, &y, &comp, req);
	
	if( data == nullptr )
	{
		return false;
	}
	
	buffer.init((uint)x, (uint)y );
	
	std::memcpy( buffer.getBuffer() , data, x*y*4);
	
	stbi_image_free(data);
	
	return true;
}
//template <> bool load( String location , String name , PixelBuffer<RGBAHigh>& buffer );
	
template <> bool save( String path , PixelBuffer<RGBALow>& buffer )
{
	String filename = path + ".png";
	return stbi_write_png(filename.c_str(), buffer.getWidth(), buffer.getHeight(), 4, buffer.getBuffer() , 0) == 1;
}
	
//template <> bool save( String location , String name , PixelBuffer<RGBAHigh>& buffer );

} // native

#endif // USE_COMMON_NATIVE

