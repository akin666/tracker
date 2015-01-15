/*
 * tracer.hpp
 *
 *  Created on: 21.10.2014
 *      Author: akin
 */

#ifndef APP_TRACKER_HPP_
#define APP_TRACKER_HPP_

#include <core.hpp>
#include "scene/scene.hpp"

class Tracker : public core::Application
{
private:
	Scene scene;
public:
	Tracker();

	virtual ~Tracker();

    virtual bool init();

    virtual void run();

    virtual bool complete();

    virtual std::string getName() const;
};

#endif /* APP_TRACKER_HPP_ */
