
#include <iostream>
#include <vector>

#include "app/tracker"
#include <traccore>
#include <config>

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
				CONFIG->set( key , value );
			}
		}
    }
	
    // first thing to run, is init application
    createSingleton<core::Application , Tracker>();

    Singleton<core::Application>::Shared app;
    do
    {
        app = singleton<core::Application>();
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
