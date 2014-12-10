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
#include "../hitinfo"

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
	return Colors::black;
	return normalToColor(ray.direction);
}

Color solve( const Scene& scene , const RayInfo& ray , const Material& medium )
{
	const float smallstep = 0.001f;
	
	// Hit solving..
	HitInfo hit;
	scene.trace( ray , hit );
	float distance = ray.distance + hit.distance;
	int bounces = ray.bounces + 1;
	
	Color transparency = Color(1.0f) - glm::min( (Color(1.0f) - medium.transparency ) * distance , Color(1.0f) );
	if( distance > scene.max || bounces > 10 )
	{
		return infinite(ray) * transparency;
	}
	
	if( hit.count <= 0 )
	{
		// No hit..
		return infinite(ray);
	}
	
	//// Solving the ray traversal till the hit point
	// Transparency
	if( transparency == Colors::black )
	{
		return Colors::black;
	}
	
	// If hit.inside < 0, then we are hitting the object from inside
	const Material& material = hit.material;
	
	Color result = Colors::black;
	
	// see through?
	// Refraction?
	glm::vec3 direction = ray.direction;
	if( material.refraction.r > 0.0f )
	{
		float refraction = medium.refraction.r / material.refraction.r;
		float cosI = glm::dot( hit.normal, ray.direction );
		float cosT2 = 1.0f - refraction * refraction * (1.0f - cosI * cosI);
		
		float sqf = glm::sqrt( cosT2 );
		
		if( !isnan(sqf) )
		{
			direction = (refraction * ray.direction) + (refraction * cosI - sqf) * hit.normal;
		}
	}
	
	RayInfo itmp( Ray( hit.point + ( direction * smallstep ) , direction ) , distance , bounces );
	result += solve( scene , itmp , material );
	
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
		RayInfo itmp( Ray( hit.point + ( direction * smallstep ) , direction ) , distance , bounces );
		
		Color reflection = solve( scene , itmp , medium );
		
		result += reflection * material.reflection;
	}
	
	// Emissive
	result += material.emission;
	
	// Ambient
	result += material.diffuse * scene.ambient;
	
	return result * transparency;
}

} // namespace devns
	
Color dev( const Scene& scene , const Ray& ray )
{
	// we need more "Rich" ray.. add material & length..
	RayInfo rayinfo( ray );
	
	const Material& medium = scene.getMaterialAt( ray.position );
	
	return devns::solve( scene , rayinfo , medium );
}

} // namespace solver
