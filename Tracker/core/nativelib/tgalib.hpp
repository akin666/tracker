/* 
 * File:   tgalib.h
 * Author: akin
 *
 * Created on 20. lokakuuta 2014, 21:03
 */

#ifndef TGALIB_H
#define	TGALIB_H

#include <string>

namespace tgalib 
{
    bool RGBA8InterleavedWrite( std::string filename , int width , int height , const void *pixels );
    bool RGB8InterleavedWrite( std::string filename , int width , int height , const void *pixels );
    bool ALPHA8Write( std::string filename , int width , int height , const void *pixels );

    bool RGBA8Write( std::string filename , int width , int height , const void *pixels );
    bool RGB8Write( std::string filename , int width , int height , const void *pixels );
}

#endif	/* tgalib */

