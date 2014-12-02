/*
 * config
 *
 *  Created on: 16.6.2012
 *      Author: akin
 */

#include "config"

template <>
void Config::set<std::string>( std::string key , const std::string& value)
{
	auto iter = keys.find( key );
	if( iter == keys.end() )
	{
		strings.push_back( value );
		keys[key] = strings.size();
	}
	strings[ iter->second ] = value;
}

template <>
void Config::set<float>( std::string key , const float& value)
{
	auto iter = keys.find( key );
	if( iter == keys.end() )
	{
		floats.push_back( value );
		keys[key] = floats.size();
	}
	floats[ iter->second ] = value;
}

template <>
bool Config::get<float>( std::string key , float def , float& target )
{
	auto iter = keys.find( key );
	if( iter == keys.end() )
	{
		target = def;
		return false;
	}
	target = floats[ iter->second ];
	return true;
}

template <>
bool Config::get<std::string>( std::string key , std::string def , std::string& target )
{
	auto iter = keys.find( key );
	if( iter == keys.end() )
	{
		target = def;
		return false;
	}
	target = strings[ iter->second ];
	return true;
}