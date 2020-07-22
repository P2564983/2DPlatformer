#pragma once

/*!
\file StaticBlock.h
*/

#include <Box2D/Box2D.h>
#include <SFML/Graphics.hpp>

#include "PhysicalThing.h"

/*! \class StaticBlock
\brief A simple block which can not move or rotate but can collide with stuff
*/

class StaticBlock : public sf::RectangleShape, public PhysicalThing
{
public:
	StaticBlock(
		b2World * world, 
		const sf::Vector2f& position, 
		const sf::Vector2f& size, 
		const float& orientation,
		CollisionFilter type
	); //!< Complete contructor
};