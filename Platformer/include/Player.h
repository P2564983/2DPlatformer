#pragma once

/*!
\file Player.h
*/

#include <Box2D/Box2D.h>
#include <SFML/Graphics.hpp>

#include "DynamicBlock.h"

/*! \class Player
\brief A controllable character in the world
*/

using namespace sf;

class Player : public DynamicBlock
{
public:
	Player(b2World* world, const sf::Vector2f& position);
	
	// Player movement
	void move(const b2Vec2& offset) const;
};