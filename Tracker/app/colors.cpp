/*
 * colors.cpp
 *
 *  Created on: 24.10.2014
 *      Author: akin
 */

#include "colors"

#define RGB_TO_COLOR
// #define RGB_TO_COLOR rgb2hsb

const Color Colors::clear = RGB_TO_COLOR( Color( 0.0f , 0.0f , 0.0f ) );

const Color Colors::white = RGB_TO_COLOR( Color( 1.0f , 1.0f , 1.0f ) );
const Color Colors::black = RGB_TO_COLOR( Color( 0.0f , 0.0f , 0.0f ) );
const Color Colors::grey = RGB_TO_COLOR( Color( 0.5f , 0.5f , 0.5f ) );

const Color Colors::red = RGB_TO_COLOR( Color( 1.0f , 0.0f , 0.0f ) );
const Color Colors::green = RGB_TO_COLOR( Color( 0.0f , 1.0f , 0.0f ) );
const Color Colors::blue = RGB_TO_COLOR( Color( 0.0f , 0.0f , 1.0f ) );

const Color Colors::teal = RGB_TO_COLOR( Color( 0.0f , 1.0f , 1.0f ) );
const Color Colors::yellow = RGB_TO_COLOR( Color( 1.0f , 1.0f , 0.0f ) );
const Color Colors::magenta = RGB_TO_COLOR( Color( 1.0f , 0.0f , 1.0f ) );

Colors::Colors()
{
	colors["clear"] = clear;
	colors["white"] = white;
	colors["black"] = black;
	colors["grey"] = grey;
	colors["red"] = red;
	colors["green"] = green;
	colors["blue"] = blue;
	colors["teal"] = teal;
	colors["yellow"] = yellow;
}

void Colors::random( Color& out )
{
	out = RGB_TO_COLOR( Color( core::random<float32>() , core::random<float32>() , core::random<float32>() ) );
}

void Colors::set( std::string key , const Color& color )
{
	colors[key] = color;
}

bool Colors::get( std::string color , Color& out ) const
{
	auto iter = colors.find(color);
	if( iter == colors.end() )
	{
		return false;
	}
	out = iter->second;
	return true;
}

#undef RGB_TO_COLOR

