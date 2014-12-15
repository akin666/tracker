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

void log( String what , CScriptVar* c )
{
	LOG->message("%s: %s" , what.c_str() , c->getFlagsAsString().c_str() );
	for( auto *child = c->firstChild ; child != nullptr ; child = child->nextSibling )
	{
		auto *data = child->var;
		LOG->message("%s type: %s" , child->name.c_str() , data->getFlagsAsString().c_str() );
	}
}

// Config.getString( key , def );
void configGetString(CScriptVar *c, void *userdata)
{
	auto *child = c->firstChild;
	if( child == nullptr ||
	    child->nextSibling == nullptr || // key
	    child->nextSibling->nextSibling == nullptr || // def
	    child->nextSibling->nextSibling->nextSibling == nullptr ) // return
	{
		LOG->error("%s:%d Script failed to read config." , __FILE__ , __LINE__ );
		return;
	}
	
	auto *key = child->nextSibling;
	auto *def = key->nextSibling;
	auto *ret = def->nextSibling;
	
	if( !(key->var->isString() && def->var->isString()) )
	{
		LOG->error("%s:%d Script failed to read config." , __FILE__ , __LINE__ );
		return;
	}
	
	String found = CONFIG->get( key->var->getString() , def->var->getString() );
	
	ret->var;
}

void configSetString(CScriptVar *c, void *userdata)
{
	LOG->message("setstr js scripting");
}

void logError(CScriptVar *c, void *userdata)
{
	String str;
	for( auto *child = c->firstChild ; child != nullptr ; child = child->nextSibling )
	{
		auto *data = child->var;
		if( data->isString() )
		{
			str.append(data->getString());
		}
	}
	
	if( !str.empty() )
	{
		LOG->error("Init Script: %s", str.c_str() );
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
	if( !native::load( "" , CONFIG->get<String>("initfile" , "init.js") , script ) )
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
	try
	{
		js->execute( script );
	}
	catch(std::exception& ex)
	{
		LOG->error("%s:%i Init Script failed: %s", __FILE__ , __LINE__, ex.what() );
	}
	catch(...)
	{
		LOG->error("%s:%i Init Script failed!", __FILE__ , __LINE__ );
	}
}

bool Init::complete()
{
    return false;
}

String Init::getName() const
{
	return "Init";
}

}
