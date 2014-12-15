/*
 * log.cpp
 *
 *  Created on: 16.6.2012
 *      Author: akin
 */

#include "log"

#define USE_COMMON_LOG
#ifdef USE_COMMON_LOG

#include <iostream>
#include "native"
#include <stdarg.h>
#include <stdio.h>

#define MAX_LOG_MSG_LEN 2048

Log::Log()
{
}

Log::~Log()
{
}

bool Log::initialize()
{
	return true;
}

void Log::uninitialize()
{
}

void Log::streamIt( const String& stream , const String& message )
{
	::native::log( stream , message );
}

void Log::message( const char* format , ... )
{
	char buffer[ MAX_LOG_MSG_LEN];
	va_list args;
	va_start( args, format );
	vsnprintf( buffer, (MAX_LOG_MSG_LEN - 1), format, args);
	va_end( args );
	String msg(buffer);
	const String stream("log");
	streamIt( stream , msg );
}

void Log::error( const char* format , ... )
{
	char buffer[ MAX_LOG_MSG_LEN];
	va_list args;
	va_start( args, format );
	vsnprintf( buffer, (MAX_LOG_MSG_LEN - 1), format, args);
	va_end( args );
	String msg(buffer);
	const String stream("error");
	streamIt( stream , msg );
}

void Log::warning( const char* format , ... )
{
	char buffer[ MAX_LOG_MSG_LEN];
	va_list args;
	va_start( args, format );
	vsnprintf( buffer, (MAX_LOG_MSG_LEN - 1), format, args);
	va_end( args );
	String msg(buffer);
	const String stream("warning");
	streamIt( stream , msg );
}

void Log::print( const String& stream , const char* format , ... )
{
	char buffer[ MAX_LOG_MSG_LEN];
	va_list args;
	va_start( args, format );
	vsnprintf( buffer, (MAX_LOG_MSG_LEN - 1), format, args);
	va_end( args );
	String msg(buffer);
	streamIt( stream , msg );
}

#endif

