
#include <iostream>
#include <vector>

#include "core/init/init"
#include "core/traccore"

// package the args into string vector..
int main(int argc, char**argv) 
{
    std::vector<std::string> strvec(argc);
    for( int i = 0 ; i < argc ; ++i )
    {
        strvec.push_back( std::string(argv[i]) );
    }
	
    // first thing to run, is init application
    createSingleton<core::Application , core::Init>();

    Singleton<core::Application>::Shared app;
    do
    {
        app = singleton<core::Application>();
        // init
        if( !app->init( strvec ) )
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
