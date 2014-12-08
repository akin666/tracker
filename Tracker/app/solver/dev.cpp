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

Color solve( const Scene& scene , const RayInfo& ray )
{
	// Hit solving..
	HitInfo hit;
	scene.trace( ray , hit );
	if( (ray.distance + hit.distance) > scene.max || ray.bounces > 5 )
	{
		return infinite(ray);
	}
	
	if( hit.count <= 0 )
	{
		// No hit..
		return infinite(ray);
	}
	
	// If hit.inside < 0, then we are hitting the object from inside
	const Material& medium = hit.medium;
	const Material& material = hit.material;
	
	Color result = Colors::black;
	
	//// Solving the ray traversal till the hit point
	// Transparency
	// Some visibility is taken out, by the ray..
	// transparency is: "How much light gets through the object"
	// This actually can reach opaque levels, and then we dont need to solve
	// about what happens at the surface.
	// IS IT ADDITIVE? NO! jeez.. TODO
	
	// WE are responsible from ray.position to hit.point, all that happens there, is our responsibility
	// First we need to solve the ray material and whether the ray even gets to the surface hitpoint
	// Then we need to solve the surface on the hitpoint
	if( material.name == "green" )
	{
		int i = 0;
	}
	Color transparency = Color(1.0f) - glm::min( (Color(1.0f) - medium.transparency ) * hit.distance , Color(1.0f) );
	if( transparency != Colors::black )
	{
		// Refraction?!? TODO
		RayInfo itmp( Ray( hit.point + ( ray.direction * 0.001f ) , ray.direction ) , ray.distance + hit.distance , ray.bounces + 1 );
		
		result += solve( scene , itmp ) * transparency;
	}
	
	//// Solving the hit surface
	// how does this material react on the surface..
	// It hit something..
	{
		glm::vec3 normalEpsilon = hit.normal * (std::numeric_limits<float>::epsilon());
		glm::vec3 hitpointOut = hit.point + normalEpsilon;
		glm::vec3 hitpointIn = hit.point - normalEpsilon;
		
		std::vector<Node*> lights;
		
		scene.getLights( hit , lights );
		
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
			float distance = glm::length( diff );
			
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
	
	// Reflection
	if( (material.reflection.r + material.reflection.g + material.reflection.b) > 0.0f )
	{
		glm::vec3 direction = ray.direction - 2.0f * glm::dot( ray.direction , hit.normal ) * hit.normal;
		RayInfo itmp( Ray( hit.point , direction ) , ray.distance + hit.distance , ray.bounces + 1 );
		
		Color reflection = solve( scene , itmp );
		
		result += reflection * material.reflection;
	}
	
	// Emissive
	result += material.emission;
	
	// Ambient
	result += material.diffuse * scene.ambient;
	
	return result;
}

} // namespace devns
	
Color dev( const Scene& scene , const Ray& ray )
{
	// we need more "Rich" ray.. add material & length..
	RayInfo rayinfo( ray );
	
	return devns::solve( scene , rayinfo );
}

} // namespace solver
