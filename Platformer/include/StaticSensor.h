#pragma once

/*!
\file staticSensor.h
*/

#include <Box2D/Box2D.h>
#include <SFML/Graphics.hpp>
#include <iostream>

#include "PhysicalThing.h"

/*! \class StaticSensor
\brief An abstract class for implementing sensors
*/

class StaticSensor : public sf::RectangleShape, public PhysicalThing
{
public:
	void initRectangle(b2World* world, sf::Vector2f position, sf::Vector2f size, float orientation);
	void initCircle(b2World* world, sf::Vector2f position, float radius);
	virtual void onAction(b2Body* other) = 0; //!< Thing the sensor does when hit
	virtual void offAction(b2Body* other) = 0; //!< Thing the sensor does when hit stops
};