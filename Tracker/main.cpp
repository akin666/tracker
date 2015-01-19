
#include "defines.hpp"

#include <iostream>
#include <vector>

#include "app/tracker.hpp"
#include <core.hpp>
#include <config.hpp>

// the blody easylogging requires this..
// (I hate when random libraries pollute my codebase with their nonsense)
INITIALIZE_EASYLOGGINGPP

// package the args into string vector..
int main(int argc, char**argv) 
{
	// configure logging
	el::Loggers::reconfigureAllLoggers(el::ConfigurationType::Format, "%datetime - %level@%fbase:%line: %msg");
	
	// load config.
	try
	{
		core::config::load("init.json");
	}
	catch( ... )
	{
		LOG(ERROR) << " Application failed to configuration!";
	}
	
	// skip 1st argument, it is the executable name..
    std::vector<std::string> args(argc);
    for( int i = 1 ; i < argc ; ++i )
    {
		std::string str( argv[i] );
		
		if( str.size() < 2 || i >= argc - 1 )
		{
			continue;
		}
		
		if( str.at( 0 ) == '-' )
		{
			++i;
			
			// skip '-'
			auto key = str.substr( 1 );
			std::string value( argv[i] );
			if( value.size() > 1 )
			{
				core::config::set<std::string>( key , value );
			}
		}
    }
	
    // first thing to run, is init application
    core::Application::Shared app = std::dynamic_pointer_cast<core::Application>( std::make_shared<Tracker>() );
    do
    {
        // init
        if( !app->init() )
        {
			LOG(ERROR) << app->getName() << " Application init failed!";

            // Failed!
            return -1;
		}
		LOG(INFO) << app->getName() << " is running.";
        app->run();
    }
    while( app && !app->complete() );

    return 0;
}
