/* 
 * File:   tgalib.cpp
 * Author: akin
 * 
 * Created on 20. lokakuuta 2014, 21:03
 */

#include "tgalib.hpp"

#include <fstream>
#include <iostream>
#include <vector>

namespace tgalib 
{
    bool RGBA8InterleavedWrite( std::string filename , int width , int height , const void *pixels )
    {
        //Error checking
        if( pixels == NULL || width <= 0 || height <= 0 )
        {
            std::cout << "Image size is not set properly" << std::endl;
            return false;
        }

        std::ofstream o(filename.c_str(), std::ios::out | std::ios::binary);

        //Write the header
        o.put(0);
        o.put(0);
        o.put(2);                         // uncompressed RGB
        o.put(0); 	o.put(0);
        o.put(0); 	o.put(0);
        o.put(0);
        o.put(0); 	o.put(0);           // X origin
        o.put(0); 	o.put(0);           // y origin
        o.put((width & 0x00FF));
        o.put((width & 0xFF00) / 256);
        o.put((height & 0x00FF));
        o.put((height & 0xFF00) / 256);
        o.put(32);                        // 24 bit bitmap
        o.put(0);

        //Write the pixel data
        int max = height * width * 4;
        for( int i = 0 ; i < max ;i += 4 )
        {
            o.put( ((char*)pixels)[i+2] );
            o.put( ((char*)pixels)[i+1] );
            o.put( ((char*)pixels)[i+0] );
            o.put( ((char*)pixels)[i+3] );
            // BGRA
        }

        //close the file
        o.close();

        return true;
    }

    bool RGB8InterleavedWrite( std::string filename , int width , int height , const void *pixels )
    {
        //Error checking
        if( pixels == NULL || width <= 0 || height <= 0 )
        {
            std::cout << "Image size is not set properly" << std::endl;
            return false;
        }

        std::ofstream o(filename.c_str(), std::ios::out | std::ios::binary);

        //Write the header
        o.put(0);
        o.put(0);
        o.put(2);                         // uncompressed RGB
        o.put(0); 	o.put(0);
        o.put(0); 	o.put(0);
        o.put(0);
        o.put(0); 	o.put(0);           // X origin
        o.put(0); 	o.put(0);           // y origin
        o.put((width & 0x00FF));
        o.put((width & 0xFF00) / 256);
        o.put((height & 0x00FF));
        o.put((height & 0xFF00) / 256);
        o.put(32);                        // 24 bit bitmap
        o.put(0);

        //Write the pixel data
        int max = height * width * 3;
        for( int i = 0 ; i < max ;i += 3 )
        {
            o.put( ((char*)pixels)[i+2] );
            o.put( ((char*)pixels)[i+1] );
            o.put( ((char*)pixels)[i+0] );
            o.put( (char)0xFF );
            // BGRA
        }

        //close the file
        o.close();

        return true;
    }

    bool ALPHA8Write( std::string filename , int width , int height , const void *pixels )
    {
        //Error checking
        if( pixels == NULL || width <= 0 || height <= 0 )
        {
            std::cout << "Image size is not set properly" << std::endl;
            return false;
        }

        std::ofstream o(filename.c_str(), std::ios::out | std::ios::binary);

        //Write the header
        o.put(0);
        o.put(0);
        o.put(2);                         // uncompressed RGB
        o.put(0); 	o.put(0);
        o.put(0); 	o.put(0);
        o.put(0);
        o.put(0); 	o.put(0);           // X origin
        o.put(0); 	o.put(0);           // y origin
        o.put((width & 0x00FF));
        o.put((width & 0xFF00) / 256);
        o.put((height & 0x00FF));
        o.put((height & 0xFF00) / 256);
        o.put(32);                        // 24 bit bitmap
        o.put(0);

        //Write the pixel data
        int max = height * width;
        for( int i = 0 ; i < max ; i++ )
        {
            o.put( ((char*)pixels)[i] );
            o.put( ((char*)pixels)[i] );
            o.put( ((char*)pixels)[i] );
            o.put( ((char*)pixels)[i] );
            // BGRA
        }   

        //close the file
        o.close();

        return true;
    }

    bool RGBA8Write( std::string filename , int width , int height , const void *pixels )
    {
        // convert RGBARGBA... -> RRR...GGG...BBB...AAA...
        int total = width * height;

        std::vector<unsigned char> target;
        target.resize( total * 4 );

        unsigned char *tr = (unsigned char *)pixels;
        unsigned char *tg = (unsigned char *)pixels + ( total );
        unsigned char *tb = (unsigned char *)pixels + ( 2 * total );
        unsigned char *ta = (unsigned char *)pixels + ( 3 * total );

        for( int i = 0 ; i < total ; ++i )
        {
            target[ i * 4 + 0 ] = tr[i];
            target[ i * 4 + 1 ] = tg[i];
            target[ i * 4 + 2 ] = tb[i];
            target[ i * 4 + 3 ] = ta[i];
        }

        return RGBA8InterleavedWrite(filename , width , height , &target[ 0 ] );
    }

    bool RGB8Write( std::string filename , int width , int height , const void *pixels )
    {
        // convert RGBARGBA... -> RRR...GGG...BBB...AAA...
        int total = width * height;

        std::vector<unsigned char> target;
        target.resize( total * 3 );

        unsigned char *tr = (unsigned char *)pixels;
        unsigned char *tg = (unsigned char *)pixels + ( total );
        unsigned char *tb = (unsigned char *)pixels + ( 2 * total );

        for( int i = 0 ; i < total ; ++i )
        {
            target[ i * 3 + 0 ] = tr[i];
            target[ i * 3 + 1 ] = tg[i];
            target[ i * 3 + 2 ] = tb[i];
        }

        return RGB8InterleavedWrite(filename , width , height , &target[ 0 ] );
    }
} // tgalib