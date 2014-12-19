//
//  outputvideo.cpp
//  Tracker
//
//  Created by mikael korpela on 03/11/14.
//  Copyright (c) 2014 mikael korpela. All rights reserved.
//

#include "outputvideo"
#include <native>

namespace output
{
	
bool Video::init( String name, String path , int width , int height , pixelformat::Format inputformat , int dpi , int framerate )
{
	if( out.is_open() )
	{
		return false;
	}
	
	this->name = name;
	
	const char* pixelformat = pixelformat::getName(inputformat);
	
	if( pixelformat == nullptr )
	{
		return false;
	}
	
	// filename to contain
	// [NAME]_ENC_[WIDTH]x[HEIGHT]_[DPI]_[PIXELFORMAT]_fr[FRAMERATE].yuv
	const int maxbuffer = 512;
	char buffer[ maxbuffer ];
	snprintf( buffer, (maxbuffer - 1), "%s_ENC_%dx%d_%d_%s_fr%d.yuv" , path.c_str() , width , height , dpi , pixelformat , framerate );
	
	out.open( String(buffer) , std::ios::out | std::ios::binary );
	
	return true;
}
	
void Video::append( const void *pixels , size_t count )
{
	out.write( (const char*)pixels, count );
}

void Video::close()
{
	out.close();
}

String Video::getName() const
{
	return name;
}
	
}