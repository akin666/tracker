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
namespace scrpting {
	
void configGetString(CScriptVar *c, void *userdata)
{
	LOG->message("getstr js scripting");
}

void configSetString(CScriptVar *c, void *userdata)
{
	LOG->message("setstr js scripting");
}

void logError(CScriptVar *c, void *userdata)
{
	LOG->message("logerr js scripting");
}
	
}

Init::Init()
: js( new CTinyJS )
, initialized(false)
{
}

Init::~Init()
{
	delete js;
	js = nullptr;
}

bool Init::init()
{
	if( initialized )
	{
		return true;
	}
	
	// init systems..
	if( !native::readFile( "" , CONFIG->get<std::string>("initfile" , "init.js") , script ) )
	{
		LOG->error("%s:%d Failed to read init file." , __FILE__ , __LINE__ );
		return false;
	}
	
	js->addNative("function Config.getString(key)", scrpting::configGetString, 0);
	js->addNative("function Log.error(msg)", scrpting::logError, 0);
	
	initialized = true;
    return true;
}

void Init::run()
{
	// init the next app..
	createSingleton<core::Application , ::Tracker>();
	js->execute( script );
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
