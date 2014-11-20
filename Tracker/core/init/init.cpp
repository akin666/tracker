/* 
 * File:   application.cpp
 * Author: akin
 * 
 * Created on 20. lokakuuta 2014, 21:10
 */

#include "init"

#include "../../app/tracker"
#include "../traccore"


namespace core  {

Init::Init()
{
}

Init::~Init()
{
}

bool Init::init( const std::vector<std::string>& args )
{
	// init systems..

	// init the next app..
    createSingleton<core::Application , ::Tracker>();
    return true;
}

void Init::run()
{
}

bool Init::complete()
{
    return false;
}

std::string Init::getName()
{
	return "Init";
}

}
