/*
 * sceneloader
 *
 *  Created on: 21.10.2014
 *      Author: akin
 */

#include "sceneloader.hpp"
#include <json/json.h>
#include <fstream>

#include "scene/sphere.hpp"
#include "scene/disc.hpp"
#include "scene/camera.hpp"

#include <graphics/sampler/color.hpp>
#include <graphics/sampler/buffer.hpp>
#include <graphics/buffer2d.hpp>

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

bool read( const Json::Value& value, Manager& manager, core::graphics::Sampler::Shared& val )
{
	if( value.isNull() )
	{
		return false;
	}
	
	if( value.isString() )
	{
		// seek sampler from manager
		return manager.get( value.asString() , val );
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
		
		Sampler::Shared ssampler(new SamplerColor(color));
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
		
		Sampler::Shared ssampler(new SamplerColor(color));
		val = ssampler;
		
		return true;
	}
	else if( type == "texture" )
	{
		std::string path;
		if( !read( value["path"] , path ) )
		{
			return false;
		}
		
		auto *ptr = new PixelBuffer<RGBALow>();
		
		if( !native::load( path , *ptr ) )
		{
			LOG->error("Failed to load %s", path.c_str());
			delete ptr;
			return false;
		}
		
		Sampler::Shared ssampler(ptr);
		val = ssampler;
		
		return true;
	}
	
	LOG->error("Unknown sampler type.");
	return false;
}

bool read( const Json::Value& value , Manager& manager , Material& val )
{
	if( value.isNull() )
	{
		return false;
	}
	
	if( value.isString() )
	{
		return manager.get( value.asString() , val );
	}
	
	if(!value.isObject())
	{
		return false;
	}
	
	read( value["name"] , val.name );
	read( value["reflection"] , manager , val.reflection );
	read( value["emission"] , manager , val.emission );
	read( value["transparency"] , manager , val.transparency );
	read( value["diffuse"] , manager , val.diffuse );
	read( value["refraction"] , manager , val.refraction );
	
	return true;
}

bool read( const Json::Value& value , Manager& manager , Node& val )
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

bool read( const Json::Value& value , Manager& manager , Camera& val )
{
	if( value.isNull() || (!value.isObject()) )
	{
		return false;
	}
	
	read( value , manager , (Node&)val );
	
	float dpi;
	
	read( value["scale"] , val.scale );
	read( value["distance"] , val.distance );
	read( value["width"] , val.width );
	read( value["height"] , val.height );
	read( value["dpi"] , dpi );
	
	val.dpmm = dpi2dpmm( dpi );
	
	return true;
}

bool read( const Json::Value& value , Manager& manager , Sphere& val )
{
	if( value.isNull() || (!value.isObject()) )
	{
		return false;
	}
	
	read( value , manager , (Node&)val );
	read( value["radius"] , val.radius );
	read( value["material"] , manager , val.material );

	return true;
}

bool read( const Json::Value& value , Manager& manager , Disc& val )
{
	if( value.isNull() || (!value.isObject()) )
	{
		return false;
	}
	
	read( value , manager , (Node&)val );
	read( value["radius"] , val.radius );
	read( value["material"] , manager , val.material );
	
	return true;
}

bool SceneLoader::load( std::string path , Scene& scene )
{
	Manager& manager = scene.getManager();
	
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
		read( settings["ambient"] , manager , scene.ambient );
	}
	
	const Json::Value& samplers = root["samplers"];
	if( !samplers.isNull() && samplers.isArray() )
	{
		Sampler::Shared sampler;
		std::string name;
		
		// extract samplers
		for( int i = 0 ; i < samplers.size() ; ++i )
		{
			sampler.reset();
			const auto& jssampler = samplers[i];
			
			read( jssampler["name"] , name );
			read( jssampler , manager , sampler );
			
			manager.set( name , sampler );
		}
	}
	
	const Json::Value& materials = root["materials"];
	if( !materials.isNull() && materials.isArray() )
	{
		// extract materials
		for( int i = 0 ; i < materials.size() ; ++i )
		{
			// material needs to be empty, fresh, thats why it is redone in loop..
			Material material;
			const auto& jsmaterial = materials[i];
			
			read( jsmaterial , manager , material );
			
			manager.set( material.name , material );
		}
	}
	
	const Json::Value& cameras = root["cameras"];
	if( !cameras.isNull() && cameras.isArray() )
	{
		std::string name;
		
		for( int i = 0 ; i < cameras.size() ; ++i )
		{
			const auto& jsmcamera = cameras[i];
			
			auto *camera = new Camera;
			
			if( !read( jsmcamera , manager , *camera ) )
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
				
				if( !read(jsnode , manager , *sphere ) )
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
				
				if( !read(jsnode , manager , *disc ) )
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
	manager.get( "air" , air );
	scene.setMaterial( air );
	
	return true;
}
