/*
 * sceneloader
 *
 *  Created on: 21.10.2014
 *      Author: akin
 */

#include "sceneloader"
#include <json/json.h>
#include <fstream>

#include "scene/sphere"
#include "scene/disc"
#include "scene/camera"

#include <colorsampler>

// glm::translate
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/quaternion.hpp>
#include <glm/ext.hpp>


bool read( const Json::Value& value , float& val )
{
	if( value.isNull() || (!value.isNumeric()) )
	{
		return false;
	}
	val = value.asFloat();
	return true;
}

bool read( const Json::Value& value , std::string& val )
{
	if( value.isNull() || (!value.isString()) )
	{
		return false;
	}
	val = value.asString();
	return true;
}

bool read( const Json::Value& value , glm::vec3& val )
{
	if( value.isNull() )
	{
		return false;
	}
	
	const auto a = value["x"];
	const auto b = value["y"];
	const auto c = value["z"];
	if( a.isNull() || b.isNull() || c.isNull() ||
	   (!a.isNumeric()) || (!b.isNumeric()) || (!c.isNumeric()) )
	{
		return false;
	}
	val.x = a.asFloat();
	val.y = b.asFloat();
	val.z = c.asFloat();
	return true;
}

bool read( const Json::Value& value, Scene& scene, Sampler::Shared& val )
{
	if( value.isNull() )
	{
		return false;
	}
	
	if( value.isString() )
	{
		// seek color from COLORS
		return scene.get( value.asString() , val );
	}
	
	std::string type;
	if( !read( value["type"] , type ) )
	{
		// no type specified, skip.
		LOG->error("%s:%d no type specified for node!" , __FILE__ , __LINE__ );
		return false;
	}
	
	if( type == "color" )
	{
		const auto a = value["r"];
		const auto b = value["g"];
		const auto c = value["b"];
		if( a.isNull() || b.isNull() || c.isNull() ||
		   (!a.isNumeric()) || (!b.isNumeric()) || (!c.isNumeric()) )
		{
			return false;
		}
		Color color( a.asFloat() , b.asFloat() , c.asFloat() );
		
		Sampler::Shared ssampler(new ColorSampler(color));
		val = ssampler;
		
		return true;
	}
	else if( type == "refraction" )
	{
		const auto a = value["value"];
		if( a.isNull() || (!a.isNumeric()) )
		{
			return false;
		}
		Color color( a.asFloat() );
		
		Sampler::Shared ssampler(new ColorSampler(color));
		val = ssampler;
		
		return true;
	}
	
	LOG->error("Unknown sampler type.");
	return false;
}

bool read( const Json::Value& value , Scene& scene , Material& val )
{
	if( value.isNull() )
	{
		return false;
	}
	
	if( value.isString() )
	{
		return scene.get( value.asString() , val );
	}
	
	if(!value.isObject())
	{
		return false;
	}
	
	read( value["reflection"] , scene , val.reflection );
	read( value["emission"] , scene , val.emission );
	read( value["transparency"] , scene , val.transparency );
	read( value["diffuse"] , scene , val.diffuse );
	read( value["refraction"] , scene , val.refraction );
	read( value["name"] , val.name );
	
	return true;
}

bool read( const Json::Value& value , Scene& scene , Node& val )
{
	if( value.isNull() )
	{
		return false;
	}
	
	if(!value.isObject())
	{
		return false;
	}
	
	read( value["name"] , val.name );
	
	// to origo
	val.reset();
	
	glm::vec3 position;
	glm::vec3 orientation;
	
	if( read( value["orientation"] , orientation ) )
	{
		val.rotate(orientation);
	}
	if( read( value["position"] , position ) )
	{
		val.move(position);
	}
	
	return true;
}

bool read( const Json::Value& value , Scene& scene , Camera& val )
{
	if( value.isNull() || (!value.isObject()) )
	{
		return false;
	}
	
	read( value , scene , (Node&)val );
	
	float dpi;
	
	read( value["scale"] , val.scale );
	read( value["distance"] , val.distance );
	read( value["width"] , val.width );
	read( value["height"] , val.height );
	read( value["dpi"] , dpi );
	
	val.dpmm = dpi2dpmm( dpi );
	
	return true;
}

bool read( const Json::Value& value , Scene& scene , Sphere& val )
{
	if( value.isNull() || (!value.isObject()) )
	{
		return false;
	}
	
	read( value , scene , (Node&)val );
	read( value["radius"] , val.radius );
	read( value["material"] , scene , val.material );

	return true;
}

bool read( const Json::Value& value , Scene& scene , Disc& val )
{
	if( value.isNull() || (!value.isObject()) )
	{
		return false;
	}
	
	read( value , scene , (Node&)val );
	read( value["radius"] , val.radius );
	read( value["material"] , scene , val.material );
	
	return true;
}

bool SceneLoader::load( std::string path , Scene& scene )
{
	Json::Value root;
	Json::Reader reader;
	
	std::ifstream in(path);
	
	if( !in.is_open() )
	{
		LOG->error( "could not open %s." , path.c_str() );
		return false;
	}
	
	if( !reader.parse( in , root , false ) )
	{
		LOG->error( reader.getFormatedErrorMessages().c_str() );
		return false;
	}
	
	const Json::Value& settings = root["settings"];
	if( !settings.isNull() && settings.isObject() )
	{
		// extract settings
		read( settings["name"] , scene.name );
		read( settings["type"] , scene.type );
		read( settings["maximum ray"] , scene.max );
		read( settings["infinite ray"] , scene.infinite );
		read( settings["ambient"] , scene , scene.ambient );
	}
	
	const Json::Value& samplers = root["samplers"];
	if( !samplers.isNull() && samplers.isArray() )
	{
		Sampler::Shared sampler;
		std::string name;
		
		// extract samplers
		for( int i = 0 ; i < samplers.size() ; ++i )
		{
			const auto& jssampler = samplers[i];
			
			read( jssampler["name"] , name );
			read( jssampler , scene , sampler );
			
			scene.set( name , sampler );
		}
	}
	
	const Json::Value& materials = root["materials"];
	if( !materials.isNull() && materials.isArray() )
	{
		Material material;
		std::string name;
		
		// extract materials
		for( int i = 0 ; i < materials.size() ; ++i )
		{
			const auto& jsmaterial = materials[i];
			
			read( jsmaterial["name"] , name );
			read( jsmaterial , scene , material );
			
			scene.set( name , material );
		}
	}
	
	const Json::Value& cameras = root["cameras"];
	if( !cameras.isNull() && cameras.isArray() )
	{
		Material material;
		std::string name;
		
		for( int i = 0 ; i < cameras.size() ; ++i )
		{
			const auto& jsmcamera = cameras[i];
			
			auto *camera = new Camera;
			
			if( !read( jsmcamera , scene , *camera ) )
			{
				// failed to read camera..
				LOG->error("%s:%d failed to parse camera data!" , __FILE__ , __LINE__ );
				delete camera; // do not leak it..
				continue;
			}
			scene.add(camera);
		}
	}
	
	const Json::Value& nodes = root["nodes"];
	if( !nodes.isNull() && nodes.isArray() )
	{
		// extract nodes
		std::string type;
		
		for( int i = 0 ; i < nodes.size() ; ++i )
		{
			const auto& jsnode = nodes[i];
			
			if( !read( jsnode["type"] , type ) )
			{
				// no type specified, skip.
				LOG->error("%s:%d no type specified for node!" , __FILE__ , __LINE__ );
				continue;
			}
			
			if( type == "sphere" )
			{
				auto *sphere = new Sphere;
				
				if( !read(jsnode , scene , *sphere ) )
				{
					// failed to read light..
					LOG->error("%s:%d failed to parse sphere data!" , __FILE__ , __LINE__ );
					delete sphere; // do not leak it..
					continue;
				}
				
				scene.add(sphere);
				continue;
			}
			
			if( type == "disc" )
			{
				auto *disc = new Disc;
				
				if( !read(jsnode , scene , *disc ) )
				{
					// failed to read light..
					LOG->error("%s:%d failed to parse disc data!" , __FILE__ , __LINE__ );
					delete disc; // do not leak it..
					continue;
				}
				
				scene.add(disc);
				continue;
			}
		}
	}
	
	Material air;
	scene.get( "air" , air );
	scene.setMaterial( air );
	
	return true;
}
