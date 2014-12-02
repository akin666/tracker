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
#include "colors"
#include "materials"

#include "sceneloader"

#include <outputvideo>

Tracker::Tracker()
: times(0)
{
}

Tracker::~Tracker()
{
}

bool Tracker::init()
{
	SceneLoader loader;
	
	loader.load("scene.json", scene );
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
    return true;
}

void Tracker::run()
{
	LOG->message("Tracker is running");
	
	solver::solver solve = &solver::dev;
	
	glm::vec4 filmpixel;
	glm::vec4 temp;
	
	Ray ray;
	glm::vec3 position;
	glm::vec3 direction;
	
	for( const auto* camera : scene.getCameras() )
	{
		const float camwidth = camera->width * camera->scale;
		const float camheight = camera->height * camera->scale;
		const float distance = camera->distance * camera->scale;
		
		// init buffer..
		buffer.init((uint)camwidth , (uint)camheight );
		BufferTool::clear( buffer );
		
		const float halfw = camwidth * 0.5f;
		const float halfh = camheight * 0.5f;
		const float dscale = 1.0f / (camera->dpmm * M2MM); // all things in world are in meters.. mm->m
		
		glm::vec4 corigo( 0.0f , 0.0f , 0.0f , 1.0f );
		corigo = camera->getMatrix() * corigo;
		
		const uint height = buffer.getHeight();
		const uint width = buffer.getWidth();
		
		LOG->message("Rendering image %dx%d." , width , height );
		for( uint y = 0 ; y < height ; ++y )
		{
			//LOG->message("Starting line %d of %d." , y + 1 , height );
			for( uint x = 0 ; x < width ; ++x )
			{
				// center the film, and scale..
				filmpixel.x = (x - halfw) * dscale;
				filmpixel.y = (y - halfh) * dscale;
				filmpixel.z = distance;
				filmpixel.w = 1.0f;
				
				filmpixel = camera->getMatrix() * filmpixel;
				
				ray.position.x = filmpixel.x;
				ray.position.y = filmpixel.y;
				ray.position.z = filmpixel.z;
				
				temp = glm::normalize(filmpixel - corigo);
				
				ray.direction.x = temp.x;
				ray.direction.y = temp.y;
				ray.direction.z = temp.z;
				
				// cast ray solving.
				buffer.set(x, y, solve(scene , ray));
			}
			//LOG->message("Done line %d." , y + 1 );
		}
		LOG->message("Complete.");
		
		PixelBuffer<RGBALow> lowbuffer;
		BufferTool::convert( buffer , lowbuffer );
		
		int dpi = (int)dpmm2dpi(camera->dpmm);
		
		native::saveImage( "" , camera->name , lowbuffer.getWidth() , lowbuffer.getHeight() , pixelformat::RGBA8 , lowbuffer.getBuffer() );
		
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

std::string Tracker::getName() const
{
	return "Tracker";
}
