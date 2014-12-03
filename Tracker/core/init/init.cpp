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

void log( std::string what , CScriptVar* c )
{
	LOG->message("%s: %s" , what.c_str() , c->getFlagsAsString().c_str() );
	for( auto *child = c->firstChild ; child != nullptr ; child = child->nextSibling )
	{
		auto *data = child->var;
		LOG->message("%s type: %s" , child->name.c_str() , data->getFlagsAsString().c_str() );
	}
}


void configGetString(CScriptVar *c, void *userdata)
{
	if( c->isString() )
	{
	}
}

void configSetString(CScriptVar *c, void *userdata)
{
	LOG->message("setstr js scripting");
}

void logError(CScriptVar *c, void *userdata)
{
	auto *child = c->firstChild;
	if( child == nullptr )
	{
		return;
	}
	child = child->nextSibling;
	
	// this should be the error message
	auto *data = child->var;
	if( data->isString() )
	{
		LOG->message("Script error: %s", data->getString().c_str() );
	}
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
	
	js->addNative("function Config.getString(key)", scrpting::configGetString, nullptr);
	js->addNative("function Log.error(msg)", scrpting::logError, nullptr);
	
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
