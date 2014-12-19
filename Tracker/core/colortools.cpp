/*
 * COLORTOOLS
 *
 */

#include "colortools"
#include <glm/glm.hpp>

/// HSB:
const float a60 =  1.0f / 6.0f;
const float a120 = 2.0f / 6.0f;
const float a180 = 3.0f / 6.0f;
const float a240 = 4.0f / 6.0f;
const float a300 = 5.0f / 6.0f;
const float a360 = 1.0f;

void rgb2hsb( const Color& from , Color& to )
{
	
	// RGB to HSB
	// Got r,g and b in floats (0-1)
	float max = glm::max( from.r , glm::max( from.g , from.b ));
	
	if( max <= 0.0f )
	{
		to.x = 0.0f;
		to.y = 0.0f;
		to.z = 0.0f;
		return;
	}
	float min = glm::min( from.r , glm::min( from.g , from.b ));
	float diff = max - min;
	
	to.s = (diff / max);
	to.b = max;
	
	if( max <= min )
	{
		to.x = 0.0f;
		return;
	}
	
	if (from.g == max)
	{
		to.x = (from.b - from.r) / diff * a60 + a120;
	}
	else if (from.b == max)
	{
		to.x = (from.r - from.g) / diff * a60 + a240;
	}
	else if (from.b > from.g)
	{
		to.x = (from.g - from.b) / diff * a60 + a360;
	}
	else
	{
		to.x = (from.g - from.b) / diff * a60;
	}
	
	if (to.x < 0.0f)
	{
		to.x += a360;
	}
}

void hsb2rgb( const Color& from , Color& to )
{
	// HSB to RGB
	// Got HSB in in floats h, s and hsbB (0-1)
	to.r = from.b;
	to.g = from.b;
	to.b = from.b;
	
	// no color, only intensity.
	if( from.s == 0.0f )
	{
		return;
	}
	
	float max = from.b;
	float dif = from.b * from.s;
	float min = from.b - dif;

	float h = from.x;

	if (h < a60)
	{
		to.r = max;
		to.g = h * dif / a60 + min;
		to.b = min;
	}
	else if (h < a120)
	{
		to.r = -(h - a120) * dif / a60 + min;
		to.g = max;
		to.b = min;
	}
	else if (h < a180)
	{
		to.r = min;
		to.g = max;
		to.b = (h - a120) * dif / a60 + min;
	}
	else if (h < a240)
	{
		to.r = min;
		to.g = -(h - a240) * dif / a60 + min;
		to.b = max;
	}
	else if (h < a300)
	{
		to.r = (h - a240) * dif / a60 + min;
		to.g = min;
		to.b = max;
	}
	else if (h <= a360)
	{
		to.r = max;
		to.g = min;
		to.b = -(h - a360) * dif / a60 + min;
	}
	else
	{
		to.r = 0.0f;
		to.g = 0.0f;
		to.b = 0.0f;
	}
}

Color rgb2hsb( Color from )
{
	Color to;
	rgb2hsb(from, to);
	return to;
}

Color hsb2rgb( Color from )
{
	Color to;
	hsb2rgb(from, to);
	return to;
}

void hsbAdd( const Color& a , const Color& b , Color& out )
{
	float max = a.x;
	float min = b.x;
	
	if( a.x < b.x )
	{
		min = a.x;
		max = b.x;
	}
	float distance = glm::abs(max - min);
	out.x = (min + max) * 0.5f;
	
	if( distance > 0.5f )
	{
		out.x += out.x > 0.5f ? -0.5f : 0.5f;
	}
	
	out.y = (a.y + b.y) * 0.5f;
	out.z = a.z + b.z;
}

void hsbMultiply( const Color& a , float multi , Color& out )
{
	out.x = a.x;
	out.y = a.y;
	out.z = a.z * multi;
}

/// HSP:
//  public domain function by Darel Rex Finley, 2006
//
//  This function expects the passed-in values to be on a scale
//  of 0 to 1, and uses that same scale for the return values.
//
//  See description/examples at alienryderflex.com/hsp.html


#define  Pr  .299
#define  Pg  .587
#define  Pb  .114

void rgb2hsp( const Color& from , Color& to )
{
	//  Calculate the Perceived brightness.
	to.p = sqrt( from.r*from.r * Pr + from.g*from.g * Pg + from.b*from.b * Pb );
	
	//  Calculate the Hue and Saturation.  (This part works
	//  the same way as in the HSV/B and HSL systems???.)
	if( from.r == from.g && from.r == from.b ) {
		to.x = 0.0f;
		to.y = 0.0f;
		return;
	}
	if( from.r >= from.g && from.r >= from.b) {   //  R is largest
		if( from.b >= from.g )
		{
			to.x = 1.0f - 1.0f / 6.0f * (from.b - from.g) / (from.r - from.g);
			to.y = 1.0f - from.g/from.r;
		}
		else
		{
			to.x = 1.0f / 6.0f * (from.g - from.b) / (from.r - from.b);
			to.y = 1.0f - from.b/from.r;
		}
	}
	else if( from.g >= from.r && from.g >= from.b ) {   //  G is largest
		if( from.r >= from.b ) {
			to.x = 2.0f / 6.0f - 1.0f / 6.0f * ( from.r - from.b ) / ( from.g - from.b );
			to.y = 1.0f - from.b / from.g;
		}
		else {
			to.x = 2.0f / 6.0f + 1.0f / 6.0f * ( from.b - from.r ) / ( from.g - from.r );
			to.y = 1.0f - from.r / from.g;
		}
	}
	else {   //  B is largest
		if( from.g >= from.r ) {
			to.x = 4.0f / 6.0f - 1.0f / 6.0f * ( from.g - from.r ) / ( from.b - from.r );
			to.y = 1.0f - from.r / from.b;
		}
		else {
			to.x = 4.0f / 6.0f + 1.0f / 6.0f * ( from.r - from.g ) / ( from.b - from.g );
			to.y=1.0f-from.g/from.b;
		}
	}
}



//  public domain function by Darel Rex Finley, 2006
//
//  This function expects the passed-in values to be on a scale
//  of 0 to 1, and uses that same scale for the return values.
//
//  Note that some combinations of HSP, even if in the scale
//  0-1, may return RGB values that exceed a value of 1.  For
//  example, if you pass in the HSP color 0,1,1, the result
//  will be the RGB color 2.037,0,0.
//
//  See description/examples at alienryderflex.com/hsp.html


void hsp2rgb( const Color& from , Color& to )
{
	float part = 0.0f;
	float minOverMax = 1.0f - from.s;
	float tmp = 0.0f;
	
	if( minOverMax > 0.0f )
	{
		if( from.x < 1.0f / 6.0f ) {   //  R>G>B
			tmp = 6.0f * ( from.x - 0.0f / 6.0f );
			part = 1.0f + tmp * ( 1.0f / minOverMax - 1.0f );
			to.b = from.p / sqrt( Pr / minOverMax / minOverMax + Pg * part * part + Pb );
			to.r = to.b / minOverMax;
			to.g = to.b + tmp * ( to.r - to.b );
		}
		else if ( from.x < 2.0f / 6.0f ) {   //  G>R>B
			tmp = 6.0f * ( -from.x + 2.0f / 6.0f );
			part = 1.0f + tmp * ( 1.0f / minOverMax - 1.0f );
			to.b = from.p / sqrt( Pg / minOverMax / minOverMax + Pr * part * part + Pb );
			to.g = to.b / minOverMax;
			to.r = to.b + tmp * ( to.g - to.b );
		}
		else if ( from.x < 3.0f / 6.0f ) {   //  G>B>R
			tmp = 6.0f * ( from.x - 2.0f / 6.0f );
			part = 1.0f + tmp * ( 1.0f / minOverMax - 1.0f );
			to.r = from.p / sqrt( Pg / minOverMax / minOverMax + Pb * part * part + Pr );
			to.g = to.r / minOverMax;
			to.b = to.r + tmp * ( to.g - to.r );
		}
		else if ( from.x < 4.0f / 6.0f) {   //  B>G>R
			tmp = 6.0f * ( -from.x + 4.0f / 6.0f );
			part = 1.0f + tmp * ( 1.0f / minOverMax - 1.0f );
			to.r = from.p / sqrt( Pb / minOverMax / minOverMax + Pg * part * part + Pr );
			to.b = to.r / minOverMax;
			to.g = to.r + tmp * ( to.b - to.r );
		}
		else if ( from.x < 5.0f / 6.0f) {   //  B>R>G
			tmp = 6.0f * ( from.x - 4.0f / 6.0f );
			part = 1.0f + tmp * ( 1.0f / minOverMax - 1.0f );
			to.g = from.p / sqrt( Pb / minOverMax / minOverMax + Pr * part * part + Pg );
			to.b = to.g / minOverMax;
			to.r = to.g + tmp * ( to.b - to.g );
		}
		else {   //  R>B>G
			tmp = 6.0f * ( -from.x + 1.0f );
			part = 1.0f + tmp * ( 1.0f / minOverMax - 1.0f );
			to.g = from.p / sqrt( Pr / minOverMax / minOverMax + Pb * part * part + Pg );
			to.r = to.g / minOverMax;
			to.b = to.g + tmp * ( to.r - to.g );
		}
	}
	else {
		if( from.x < 1.0f / 6.0f ) {   //  R>G>B
			tmp = 6.0f * from.x;
			to.r = sqrt( from.p * from.p / ( Pr + Pg * tmp * tmp ));
			to.g = to.r * tmp;
			to.b = 0.0f;
		}
		else if( from.x < 2.0f / 6.0f ) {   //  G>R>B
			tmp = 6.0f * ( -from.x + 2.0f / 6.0f );
			to.g = sqrt( from.p * from.p / ( Pg + Pr * tmp * tmp ));
			to.r = to.g * tmp;
			to.b = 0.0f;
		}
		else if( from.x < 3.0f / 6.0f ) {   //  G>B>R
			tmp = 6.0f * ( from.x - 2.0f / 6.0f );
			to.g = sqrt( from.p * from.p / ( Pg + Pb * tmp * tmp ));
			to.b = to.g * tmp;
			to.r = 0.0f;
		}
		else if( from.x < 4.0f / 6.0f ) {   //  B>G>R
			tmp = 6.0f * ( -from.x + 4.0f / 6.0f );
			to.b = sqrt( from.p * from.p / ( Pb + Pg * tmp * tmp ));
			to.g = to.b * tmp;
			to.r = 0.0f;
		}
		else if( from.x < 5.0f / 6.0f ) {   //  B>R>G
			tmp = 6.0f * ( from.x - 4.0f / 6.0f );
			to.b = sqrt( from.p * from.p / ( Pb + Pr * tmp * tmp ));
			to.r = to.b * tmp;
			to.g = 0.0f;
		}
		else {   //  R>B>G
			tmp = 6.0f * ( -from.x + 1.0f );
			to.r = sqrt( from.p * from.p / ( Pr + Pb * tmp * tmp ));
			to.b = to.r * tmp;
			to.g = 0.0f;
		}
	}
}

#undef  Pr
#undef  Pg
#undef  Pb

Color rgb2hsp( Color from )
{
	Color to;
	rgb2hsp(from, to);
	return to;
}

Color hsp2rgb( Color from )
{
	Color to;
	hsp2rgb(from, to);
	return to;
}

// YUV
// algorithm:
// http://www.equasys.de/colorconversion.html
void rgb2yuv( const Color& from , Color& to )
{
	to.r =  0.299 * from.r + 0.587 * from.g + 0.114 * from.b; // Y
	to.g = -0.147 * from.r - 0.289 * from.g + 0.436 * from.b; // U
	to.b =  0.615 * from.r - 0.515 * from.g - 0.071 * from.b; // V
}

void yuv2rgb( const Color& from , Color& to )
{
	to.r = from.r + 1.140 * from.b;
	to.g = from.r - 0.395 * from.g - 0.581 * from.b;
	to.b = from.r + 2.032 * from.g;
}

Color rgb2yuv( Color from )
{
	Color to;
	rgb2yuv(from, to);
	return to;
}

Color yuv2rgb( Color from )
{
	Color to;
	yuv2rgb(from, to);
	return to;
}

// YCbCr
// algorithm:
// http://www.equasys.de/colorconversion.html
void rgb2YCbCr( const Color& from , Color& to )
{
	to.r =  0.257 * from.r + 0.504 * from.g + 0.098 * from.b + 16;  // Y
	to.g = -0.148 * from.r - 0.291 * from.g + 0.439 * from.b + 128; // Cb
	to.b =  0.439 * from.r - 0.368 * from.g - 0.071 * from.b + 128; // Cr
}

void YCbCr2rgb( const Color& from , Color& to )
{
	Color tmp( from.r - 16 , from.g - 128 , from.b - 128 );
	
	to.r = 1.164 * tmp.r + 1.596 * tmp.b;
	to.g = 1.164 * tmp.r - 0.392 * tmp.g - 0.813 * tmp.b;
	to.b = 1.164 * tmp.r + 2.017 * tmp.g;
}

Color rgb2YCbCr( Color from )
{
	Color to;
	rgb2yuv(from, to);
	return to;
}

Color YCbCr2rgb( Color from )
{
	Color to;
	yuv2rgb(from, to);
	return to;
}
