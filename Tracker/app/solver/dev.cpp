/*
 * dev
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
namespace devns
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
	//return Colors::black;
	return normalToColor(ray.direction);
}

Color solve( const Scene& scene , const RayInfo& ray );

Color solve( const Scene& scene , const RayInfo& ray , const HitInfo& hit )
{
	Color result = ray.material.transparency * hit.distance;
	
	const Material& material = hit.material;
	
	{
		glm::vec3 normalEpsilon = hit.normal * (std::numeric_limits<float>::epsilon());
		glm::vec3 hitpointOut = hit.point + normalEpsilon;
		glm::vec3 hitpointIn = hit.point - normalEpsilon;
		
		const auto& lights = hit.lights;
		
		HitInfo tmpInfo;
		
		for( const auto *light : lights )
		{
			const glm::vec3& lightPos = light->getPosition();
			
			// line between hitpoint and light collides with something -> no light contibution
			
			// we  need to trace in do while loop, or in for loop..
			// and calculate the light contribution on the go..
			// the ray might go through several refractions and surfaces
			scene.traceTo( hit.point , light , tmpInfo );
			if( tmpInfo.count > 0 && tmpInfo.material.transparency != Colors::black )
			{
				continue;
			}
			
			const Material& lightMaterial = light->getMaterial();
			
			glm::vec3 diff = lightPos - hit.point;
			float distance = glm::distance( glm::vec3() , diff );
			
			Color lighting = lightMaterial.emission;
			
			lightAttenuation( distance , lighting );
			
			auto directionoflight = glm::normalize( diff );
			float dot = glm::dot( hit.normal , directionoflight );
			
			if ( lighting.r < 0.0f ) lighting.r = 0.0f;
			if ( lighting.g < 0.0f ) lighting.g = 0.0f;
			if ( lighting.b < 0.0f ) lighting.b = 0.0f;
			
			if( dot > 0.0f && (lighting.r > 0.0f || lighting.g > 0.0f || lighting.b > 0.0f ) )
			{
				result += dot * material.diffuse * lighting;
			}
		}
	}
	
	// Transparency
	if( material.transparency != Colors::white )
	{
		// Refraction?!? TODO
		RayInfo itmp( material , Ray( hit.point + ( ray.direction * 0.001f ) , ray.direction ) , ray.distance + hit.distance );
		
		result += solve( scene , itmp );
	}
	
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
	result += material.diffuse * scene.ambient;
	
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
	
} // namespace devns
	
Color dev( const Scene& scene , const Ray& ray )
{
	// we need more "Rich" ray.. add material & length..
	RayInfo rayinfo( scene.getMaterialAt( ray.position ) , ray );
	
	return devns::solve( scene , rayinfo );
}

} // namespace solver
