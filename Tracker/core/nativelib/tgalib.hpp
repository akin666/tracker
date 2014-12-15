/* 
 * File:   tgalib.h
 * Author: akin
 *
 * Created on 20. lokakuuta 2014, 21:03
 */

#ifndef TGALIB_H
#define	TGALIB_H

#include <stdtypes>

namespace tgalib 
{
    bool RGBA8InterleavedWrite( String filename , int width , int height , const void *pixels );
    bool RGB8InterleavedWrite( String filename , int width , int height , const void *pixels );
    bool ALPHA8Write( String filename , int width , int height , const void *pixels );

    bool RGBA8Write( String filename , int width , int height , const void *pixels );
    bool RGB8Write( String filename , int width , int height , const void *pixels );
}

#endif	/* tgalib */

