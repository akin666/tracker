/*
 * Materials
 *
 *  Created on: 24.10.2014
 *      Author: akin
 */

#include "materials"

const Material Materials::clear = Material();

Materials::Materials()
{
	materials["clear"] = clear;
}

void Materials::random( Material& out )
{
}

void Materials::set( std::string key , const Material& in )
{
	materials[key] = in;
}

bool Materials::get( std::string key , Material& out ) const
{
	auto iter = materials.find(key);
	if( iter == materials.end() )
	{
		return false;
	}
	out = iter->second;
	return true;
}

const Material& Materials::get( std::string key ) const
{
	auto iter = materials.find(key);
	if( iter == materials.end() )
	{
		return clear;
	}
	return iter->second;
}
