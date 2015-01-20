/*
 * tracer.cpp
 *
 *  Created on: 21.10.2014
 *      Author: akin
 */

#include "tracker.hpp"
#include "buffertool.hpp"
#include "scene/world.hpp"
#include "ray.hpp"
#include "solver/solver.hpp"
#include "scene/sphere.hpp"
#include <config.hpp>
#include "scene/camera.hpp"

#include "sceneloader.hpp"

#include <output/video.hpp>

using namespace core;

Tracker::Tracker()
{
}

Tracker::~Tracker()
{
}

bool Tracker::init()
{
	SceneLoader loader;
	
	loader.load( config::get<std::string>("scene" ,"scene.json") , scene );
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
	LOG(INFO) << "Tracker is running";
	
	solver::solver solve = &solver::dev;
	
	std::map<std::string, output::Video*> videos;
	
	int framerate = 60;
	// create videos for cameras..
	for( auto* camera : scene.getCameras() )
	{
		auto *video = new output::Video();
		
		auto buffer = camera->getBuffer();
		int dpi = (int)dpmm2dpi(camera->dpmm);
		
		video->init( camera->name , camera->name , buffer->width() , buffer->height() , graphics::RGBA8 , dpi , framerate );
		
		videos[camera->name] = video;
	}
	
	Ray ray;
	
	// animointi
	//for( int time = 0 ; time < 300 ; ++time )
	int time = 0;
	{
		LOG(INFO) << "Rendering frame " << time;
		// kaikille kamoille..
		for( auto* camera : scene.getCameras() )
		{
			camera->move( 0.0f , 0.0f , 0.04f );
			
			const float distance = camera->getDistance();
		
			const float halfw = camera->getWidth() * 0.5f;
			const float halfh = camera->getHeight() * 0.5f;
			const float dscale = 1.0f / (camera->getDpmm() * M2MM); // all things in world are in meters.. mm->m
		
			glm::vec3 corigo = camera->getPosition();
		
			auto buffer = camera->getBuffer();
		
			const auto width = buffer->width();
			const auto height = buffer->height();
		
			LOG(INFO) << "Rendering camera " << camera->name << width << "x" << height;
			for( uint y = 0 ; y < height ; ++y )
			{
				//LOG(INFO) << "Starting line << (y + 1) << " of " << height;
				for( uint x = 0 ; x < width ; ++x )
				{
					// center the film, and scale..
					ray.position.x = (x - halfw) * dscale;
					ray.position.y = (y - halfh) * dscale;
					ray.position.z = distance;
				
					camera->transform(ray.position);
				
					ray.direction = glm::normalize(ray.position - corigo);
				
					// cast ray solving.
					buffer->set(x, y, solve(scene , ray));
				}
				//LOG(INFO) << "Done line " << (y + 1);
			}
			LOG(INFO) << "Complete.";
		
			// still image
			if( time == 0 )
			{
				graphics::Buffer2D<graphics::RGBALow> lowbuffer;
				BufferTool::convert( *buffer , lowbuffer );
				native::save( camera->name , lowbuffer );
			}
			
			graphics::Buffer2D<graphics::YUVLow> yuvbuffer;
			size_t targetSize = BufferTool::convert( *buffer , yuvbuffer );
			
			// Get video output..
			auto iter = videos.find(camera->name);
			if( iter == videos.end() )
			{
				// not found
				continue;
			}
			
			auto *video = iter->second;
			video->append(yuvbuffer.buffer() , targetSize );
		}
	}
	
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

std::string Tracker::getName() const
{
	return "Tracker";
}
