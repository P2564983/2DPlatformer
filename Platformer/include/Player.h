#pragma once

/*!
\file Player.h
*/

#include <Box2D/Box2D.h>
#include <SFML/Graphics.hpp>

#include "PhysicalThing.h"
#include "DynamicBlock.h"

/*! \class Player
\brief A controllable character in the world
*/

class Player : public sf::Drawable, public PhysicalThing
{
private:
	DynamicBlock m_playerBlock;
public:
	Player(b2World* world, const sf::Vector2f& position, DynamicBlock dB);
	void update(); //!< Update rendering infomation 
};