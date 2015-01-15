/*
 * sceneloader
 *
 *  Created on: 21.10.2014
 *      Author: akin
 */

#ifndef APP_SCENELOADER_HPP_
#define APP_SCENELOADER_HPP_

#include <core>
#include "scene/scene.hpp"

class SceneLoader
{
public:
	bool load( std::string path , Scene& scene );
};

#endif // APP_SCENELOADER_HPP_
