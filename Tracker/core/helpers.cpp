//
//  helpers.cpp
//  Tracker
//
//  Created by mikael korpela on 03/11/14.
//  Copyright (c) 2014 mikael korpela. All rights reserved.
//

#include "helpers"

float dpi2dpmm( float dpi )
{
	return dpi * DPI2DPMM;
}

float dpmm2dpi( float dpmm )
{
	return dpmm * DPMM2DPI;
}
