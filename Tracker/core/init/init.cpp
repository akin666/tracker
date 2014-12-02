/* 
 * File:   application.cpp
 * Author: akin
 * 
 * Created on 20. lokakuuta 2014, 21:10
 */

#include "init"

#include "../../app/tracker"
#include <traccore>
#include <tiny-js/TinyJS.h>
#include <config>


namespace core  {

Init::Init()
: js( new CTinyJS )
{
}

Init::~Init()
{
	delete js;
	js = nullptr;
}

bool Init::init()
{
	std::string initcontent;
	
	// init systems..
	native::readFile( "" , CONFIG->get<std::string>("-initfile" , "init.js") , initcontent );
	
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

std::string Init::getName() const
{
	return "Init";
}

}
