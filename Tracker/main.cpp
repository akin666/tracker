
#include "defines.hpp"

#include <iostream>
#include <vector>

#include "app/tracker.hpp"
#include <core.hpp>
#include <config.hpp>

// package the args into string vector..
int main(int argc, char**argv) 
{
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
        	LOG->error( "%s Application init failed!" , app->getName().c_str());

            // Failed!
            return -1;
        }
    	LOG->print( "system", "%s running." , app->getName().c_str());
        app->run();
    }
    while( app && !app->complete() );

    return 0;
}
