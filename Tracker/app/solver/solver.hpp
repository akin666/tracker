
#ifndef APP_PATHSOLVER_HPP_
#define APP_PATHSOLVER_HPP_

#include <core.hpp>
#include "../ray.hpp"
#include "../scene/scene.hpp"

using namespace core;

namespace solver
{
	typedef Color (*solver)( const Scene& scene , const Ray& ray );
	
	Color blank( const Scene& scene , const Ray& ray );
	Color dev( const Scene& scene , const Ray& ray );
}

#endif // APP_SOLVER_HPP_
