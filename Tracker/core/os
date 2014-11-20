/*
 *  Created on: Mar 9, 2011
 *      Author: akin
 */

#ifndef _DETECTION_OS_H_
#define _DETECTION_OS_H_

//#include "src/defines.h"

#define OS_NOT_DETECTED
#define CRY_OS_NOT_DETECTED

// oses
#if defined(__unix__)
# define OS_UNIX
#endif

#if defined(__posix__)
# define OS_POSIX
#endif

// Real oses
#if defined(OS_NOT_DETECTED)
# if defined(_WIN32) or defined(WIN32)
#  define OS_WINDOWS
#  undef OS_NOT_DETECTED
# endif
#endif

#if defined(OS_NOT_DETECTED)
# if defined(__linux)
#  define OS_LINUX
#  undef OS_NOT_DETECTED
# endif
#endif

#if defined(OS_NOT_DETECTED)
# if defined(__QNX__)
#  define OS_QNX
#  undef OS_NOT_DETECTED
# endif
#endif

#if defined(OS_NOT_DETECTED)
# if defined(__ANDROID__)
#  define OS_ANDROID
#  undef OS_NOT_DETECTED
# endif
#endif

// Shit oses
#if defined(OS_NOT_DETECTED)
# if defined(__APPLE__) or defined(_APPLE_)
#  define OS_MAC
#  undef OS_NOT_DETECTED
# endif
#endif

// Real shit oses
#if defined(OS_NOT_DETECTED)
# if defined(__IPHONE__)
#  define OS_IPHONE
#  undef OS_NOT_DETECTED
# endif
#endif


#if defined(OS_NOT_DETECTED)
# if defined(__unix)
#  warning "Its a unix system, I know this,.."
# endif
#endif

#if defined(OS_NOT_DETECTED)
# if defined(__posix)
#  warning "pposiix?."
# endif
#endif

#if defined(OS_NOT_DETECTED) and defined(CRY_OS_NOT_DETECTED)
# error Operating system was not detected, Please elaborate?
#endif

#endif // _DETECTION_OS_H_ 

