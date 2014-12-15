/*
 * tracer.cpp
 *
 *  Created on: 21.10.2014
 *      Author: akin
 */

#include "tracker"
#include "buffertool"
#include "scene/world"
#include "ray"
#include "solver/solver"
#include "scene/sphere"
#include <config>
#include "scene/camera"

#include "sceneloader"

#include <outputvideo>

Tracker::Tracker()
{
}

Tracker::~Tracker()
{
}

bool Tracker::init()
{
	SceneLoader loader;
	
	loader.load( CONFIG->get<String>("scene" ,"scene.json") , scene );
	/**
	Material mirror;
	MATERIALS->get("mirror" , mirror );
	
	int count = 4;
	float jump = 7.5f;
	int half = count / 2;
	for( int z = -half ; z < half ; ++z )
	{
		for( int y = -half ; y < half ; ++y )
		{
			for( int x = -half ; x < half ; ++x )
			{
				///mirror.color = World::randomColor();
				
				Sphere *sphere = new Sphere();
				sphere->radius = 0.5f;
				sphere->setPosition( x * jump , y * jump , z * jump );
				sphere->material = mirror;
				scene.add( sphere );
			}
		}
	}
	/**/
	
	if( scene.type == "dynamic" )
	{
		// video cameras
	}
	else
	{
		// static images
	}
	
	for( auto* camera : scene.getCameras() )
	{
		camera->init();
	}
	
    return true;
}

void Tracker::run()
{
	LOG->message("Tracker is running");
	
	solver::solver solve = &solver::dev;
	
	Ray ray;
	
	for( auto* camera : scene.getCameras() )
	{
		const float distance = camera->getDistance();
		
		const float halfw = camera->getWidth() * 0.5f;
		const float halfh = camera->getHeight() * 0.5f;
		const float dscale = 1.0f / (camera->getDpmm() * M2MM); // all things in world are in meters.. mm->m
		
		glm::vec3 corigo = camera->getPosition();
		
		PixelBuffer<Color>& buffer = camera->getBuffer();
		
		const uint width = buffer.getWidth();
		const uint height = buffer.getHeight();
		
		LOG->message("Rendering image %dx%d." , width , height );
		for( uint y = 0 ; y < height ; ++y )
		{
			//LOG->message("Starting line %d of %d." , y + 1 , height );
			for( uint x = 0 ; x < width ; ++x )
			{
				// center the film, and scale..
				ray.position.x = (x - halfw) * dscale;
				ray.position.y = (y - halfh) * dscale;
				ray.position.z = distance;
				
				camera->transform(ray.position);
				
				ray.direction = glm::normalize(ray.position - corigo);
				
				// cast ray solving.
				buffer.set(x, y, solve(scene , ray));
			}
			LOG->message("Done line %d." , y + 1 );
		}
		LOG->message("Complete.");
		
		PixelBuffer<RGBALow> lowbuffer;
		BufferTool::convert( buffer , lowbuffer );
		
		int dpi = (int)dpmm2dpi(camera->dpmm);
		
		native::save( "" , camera->name , lowbuffer );
		
		output::Video video;
		
		video.init( "" , camera->name , lowbuffer.getWidth() , lowbuffer.getHeight() , pixelformat::RGBA8 , dpi , 1 );
		video.append(lowbuffer.getBuffer());
		video.close();
	}
}

bool Tracker::complete()
{
    return true; //(++times) > 10;
}

String Tracker::getName() const
{
	return "Tracker";
}
