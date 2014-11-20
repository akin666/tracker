/*
 * random.cpp
 *
 *  Created on: 25.7.2012
 *      Author: akin
 */

#include "corerandom"
#include <cmath>

namespace  core {

template <>
float32 random()
{
	return rand()/((float32)RAND_MAX);
}

template <>
float64 random()
{
	return rand()/((float64)RAND_MAX);
}

template <> float32 random( const float32 min , const float32 max )
{
	float64 diff = max - min;
	return min + (rand()/((float64)RAND_MAX) * diff );
}

template <> float64 random( const float64 min , const float64 max )
{
	float64 diff = max - min;
	return min + (rand()/((float64)RAND_MAX) * diff );
}

}