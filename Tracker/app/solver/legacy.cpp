/*
 * legacy
 *
 *  Created on: 28.10.2014
 *      Author: akin
 */
/*
#include "solver"
#include "../scene/world"
#include "../intersect"
#include "../scene/sphere"
#include "../colors"
#include "../rayinfo"

namespace solver
{
namespace legacyns
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
	glm::vec3 normalEpsilon = hit.normal * (std::numeric_limits<float>::epsilon());
	glm::vec3 hitpointOut = hit.point + normalEpsilon;
	glm::vec3 hitpointIn = hit.point - normalEpsilon;
	const Material& material = hit.material;
	
	for( const auto *light : scene.getLights() )
	{
		const glm::vec3& lightPos = light->getPosition();
		
		/*
		// line between hitpoint and light collides with something -> no light contibution
		if( lineCollides( scene , hitpointOut , lightPos ) )
		{
			continue;
		}
		* /
		
		glm::vec3 diff = lightPos - hit.point;
		
		float distance = glm::distance( glm::vec3() , diff );
		float power = glm::sqrt(distance);
		Color lighting( light->intensity - power );
		
		auto directionoflight = glm::normalize( diff );
		float dot = glm::dot( hit.normal , directionoflight );
		
		if ( lighting.r < 0.0f ) lighting.r = 0.0f;
		if ( lighting.g < 0.0f ) lighting.g = 0.0f;
		if ( lighting.b < 0.0f ) lighting.b = 0.0f;
		
		if( dot > 0.0f && (lighting.r > 0.0f || lighting.g > 0.0f || lighting.b > 0.0f ) )
		{
			result += dot * material.diffuse * lighting;
			
			glm::vec3 arr = directionoflight - 2.0f * dot * hit.normal;
			float dotspec = glm::dot( ray.direction , arr );
			if( dotspec > 0.0f )
			{
				result += glm::pow( dotspec , 20.0f ) * material.specular * lighting;
			}
		}
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
	
	// Transparency
	if( material.transparency != Colors::black )
	{
		// calculate refraction
		
		glm::vec3 refrIndexDiv = ray.material.refraction / material.refraction;
		glm::vec3 NN = glm::normalize( hit.point ) * refrIndexDiv;
		
		float cosi = -glm::dot( NN , ray.direction );
		glm::vec3 cost = glm::vec3(1.0f) - refrIndexDiv * refrIndexDiv * glm::vec3(1.0f - cosi*cosi);
		
		if( cost.r > 0.0f )
		{
			glm::vec3 T = (refrIndexDiv.r * ray.direction) + (refrIndexDiv.r * cosi - glm::sqrt(cost)) * NN.r;
			
			RayInfo itmp( material , Ray( hit.point + T * std::numeric_limits<float>::epsilon() , T ) , ray.distance + hit.distance );
			Color refraction = solve( scene , itmp );
			
			result.r += refraction.r * material.transparency.r;
		}
		if( cost.g > 0.0f )
		{
			glm::vec3 T = (refrIndexDiv.g * ray.direction) + (refrIndexDiv.g * cosi - glm::sqrt(cost)) * NN.g;
			
			RayInfo itmp( material , Ray( hit.point + T * std::numeric_limits<float>::epsilon() , T ) , ray.distance + hit.distance );
			Color refraction = solve( scene , itmp );
			
			result.g += refraction.g * material.transparency.g;
		}
		if( cost.b > 0.0f )
		{
			glm::vec3 T = (refrIndexDiv.b * ray.direction) + (refrIndexDiv.b * cosi - glm::sqrt(cost)) * NN.b;
			
			RayInfo itmp( material , Ray( hit.point + T * std::numeric_limits<float>::epsilon() , T ) , ray.distance + hit.distance );
			Color refraction = solve( scene , itmp );
			
			result.b += refraction.b * material.transparency.b;
		}
	}
	
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
	
} // namespace legacyns
	
Color legacy( const Scene& scene , const Ray& ray )
{
	// we need more "Rich" ray.. add material & length..
	RayInfo rayinfo( scene.getMaterialAt( ray.position ) , ray );
	
	return legacyns::solve( scene , rayinfo );
}

} // namespace solver
*/