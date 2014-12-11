/*
 * colorsources
 *
 *  Created on: 24.10.2014
 *      Author: akin
 */

#include "colorsources"

ColorSources::ColorSources()
{
}

void ColorSources::set( std::string key , ColorSource *in )
{
	sources[key] = in;
}

bool ColorSources::get( std::string key , ColorSource& out ) const
{
	auto iter = sources.find(key);
	if( iter == sources.end() )
	{
		return false;
	}
	out = *iter->second;
	return true;
}

const ColorSource& ColorSources::get( std::string key ) const
{
	auto iter = sources.find(key);
	if( iter == sources.end() )
	{
		throw "NOOO";
	}
	return *(iter->second);
}
