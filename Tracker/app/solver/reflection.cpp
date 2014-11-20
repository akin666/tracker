/*
 * reflection
 *
 *  Created on: 28.10.2014
 *      Author: akin
 */

#include "solver"
#include "../scene/world"
#include "../intersect"
#include "../scene/sphere"
#include "../colors"
#include "../rayinfo"

namespace solver
{
namespace reflectionns
{

Color normalToColor( const glm::vec3& normal )
{
	return Color(
				 (1.0f + normal.x) * 0.5f ,
				 (1.0f + normal.y) * 0.5f ,
				 (1.0f + normal.z) * 0.5f );
}

Color infinite( const Ray& ray )
{
	return normalToColor(ray.direction);
}

Color solve( const Scene& scene , const RayInfo& ray );

Color solve( const Scene& scene , const RayInfo& ray , const HitInfo& hit )
{
	Color result = Colors::black;
	
	const Material& material = hit.material;
	
	// Reflection
	if( (material.reflection.r + material.reflection.g + material.reflection.b) > 0.0f )
	{
		glm::vec3 direction = ray.direction - 2.0f * glm::dot( ray.direction , hit.normal ) * hit.normal;
		RayInfo itmp( ray.material , Ray( hit.point , direction ) , ray.distance + hit.distance );
		
		Color reflection = solve( scene , itmp );
		
		result += reflection * material.reflection;
	}
	
	// Emissive
	result += material.emission;
	
	// Ambient
	result += material.diffuse;
	
	return result;
}

Color solve( const Scene& scene , const RayInfo& ray )
{
	if( ray.distance < scene.max )
	{
		HitInfo hit;
		scene.trace( ray , hit );
		if( hit.count > 0 )
		{
			return solve( scene, ray, hit );
		}
	}
	return infinite(ray);
}
	
} // namespace reflectionns
	
Color dev( const Scene& scene , const Ray& ray )
{
	// we need more "Rich" ray.. add material & length..
	RayInfo rayinfo( scene.getMaterialAt( ray.position ) , ray );
	
	return reflectionns::solve( scene , rayinfo );
}

} // namespace solver
