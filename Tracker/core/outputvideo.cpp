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
	
bool Video::init( std::string location , std::string name , int width , int height , pixelformat::Format inputformat , int dpi , int framerate )
{
	if( out.is_open() )
	{
		return false;
	}
	
	const char* pixelformat = pixelformat::getName(inputformat);
	
	if( pixelformat == nullptr )
	{
		return false;
	}
	
	frameSize = width * height * pixelformat::getByteSize( inputformat );
	
	// filename to contain
	// [NAME]_ENC_[WIDTH]x[HEIGHT]_[DPI]_[PIXELFORMAT]_fr[FRAMERATE].video
	const int maxbuffer = 512;
	char buffer[ maxbuffer ];
	snprintf( buffer, (maxbuffer - 1), "%s_ENC_%dx%d_%d_%s_fr%d.video" , name.c_str() , width , height , dpi , pixelformat , framerate );
	
	// Construct a full path..
	std::string path = native::getPath( location ) + std::string(buffer);
	
	out.open( path , std::ios::out | std::ios::binary );
	
	return true;
}
	
void Video::append( const void *pixels )
{
	out.write( (const char*)pixels, frameSize );
}

void Video::close()
{
	out.close();
}
	
}