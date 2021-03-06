/* 
 * File:   scene.hpp
 * Author: akin
 *
 * Created on 20. lokakuuta 2014, 21:09
 
 Refraction
  - Screws with ray calculations, in theory, they can only screw with 90 degree angles..
    but if there be 2-n objects with refraction, the light contribution to the pixel, will
    be affected by any sorts of lights.. thus?? we need to trace ALL lights for the pixel..
    this.. just doesnt work well.. too heavy..
	optimize with light volumes? light volumes to be distorted by lenses/refraction.
  
  - definition of light volume?
 
 
 simple function that handles single channel refraction indexes?
 
 implement the channel independent raytracing? implement some functionality
 to read each refraction indexes for separate channels..
 
 -> 3+ more times rays..
 
 */

#ifndef SCENE_HPP
#define	SCENE_HPP

#include <core.hpp>
#include <ray.hpp>
#include "../material.hpp"
#include "../manager.hpp"
#include <graphics/sampler/sampler.hpp>

class HitInfo;
class Node;
class Camera;
class Scene
{
private:
	std::vector<Node*> nodes;
	std::vector<Node*> lights;
	std::vector<Camera*> cameras;
	
	Material base;
public:
	float max;
	float infinite;
	std::string name;
	std::string type;
	
	core::graphics::Sampler::Shared ambient;
private:
	Manager manager;
public:
    Scene();
    ~Scene();
	
	Manager& getManager();
	
	const Material& getMaterialAt( const glm::vec3& position ) const;

	void add( Node *node );
	void add( Camera *camera );
	
	void setMaterial( const Material& material );
	
	void getLights( const HitInfo& info , std::vector<Node*>& lights ) const;
	
	void trace( const core::Ray& ray , HitInfo& info ) const;
	void traceTo( const glm::vec3& origin , const Node *target , HitInfo& info ) const;

	std::vector<Camera*>& getCameras();
};

#endif	// SCENE_HPP

