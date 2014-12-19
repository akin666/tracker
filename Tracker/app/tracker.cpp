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
	
	std::map<String, output::Video*> videos;
	
	int framerate = 60;
	// create videos for cameras..
	for( auto* camera : scene.getCameras() )
	{
		auto *video = new output::Video();
		
		PixelBuffer<Color>& buffer = camera->getBuffer();
		int dpi = (int)dpmm2dpi(camera->dpmm);
		
		video->init( camera->name , camera->name , buffer.getWidth() , buffer.getHeight() , pixelformat::RGBA8 , dpi , framerate );
		
		videos[camera->name] = video;
	}
	
	Ray ray;
	
	// animointi
	//for( int time = 0 ; time < 300 ; ++time )
	int time = 0;
	{
		LOG->message("Rendering frame %d." , time );
		// kaikille kamoille..
		for( auto* camera : scene.getCameras() )
		{
			camera->move( 0.0f , 0.0f , 0.04f );
			
			const float distance = camera->getDistance();
		
			const float halfw = camera->getWidth() * 0.5f;
			const float halfh = camera->getHeight() * 0.5f;
			const float dscale = 1.0f / (camera->getDpmm() * M2MM); // all things in world are in meters.. mm->m
		
			glm::vec3 corigo = camera->getPosition();
		
			PixelBuffer<Color>& buffer = camera->getBuffer();
		
			const uint width = buffer.getWidth();
			const uint height = buffer.getHeight();
		
			LOG->message("Rendering camera %s %dx%d." , camera->name.c_str() , width , height );
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
				//LOG->message("Done line %d." , y + 1 );
			}
			LOG->message("Complete.");
		
			// still image
			if( time == 0 )
			{
				PixelBuffer<RGBALow> lowbuffer;
				BufferTool::convert( buffer , lowbuffer );
				native::save( camera->name , lowbuffer );
			}
			
			PixelBuffer<YUVLow> yuvbuffer;
			BufferTool::convert( buffer , yuvbuffer );
			
			// Get video output..
			auto iter = videos.find(camera->name);
			if( iter == videos.end() )
			{
				// not found
				continue;
			}
			
			auto *video = iter->second;
			video->append(yuvbuffer.getBuffer() , yuvbuffer.getUsed());
		}
	}
	
	// ffmpeg -s 384x216 -i test.yuv -vcodec libx264 test.h264
	
	for( auto iter : videos )
	{
		auto *video = iter.second;
		video->close();
		delete video;
	}
	videos.clear();
}

bool Tracker::complete()
{
    return true; //(++times) > 10;
}

String Tracker::getName() const
{
	return "Tracker";
}
