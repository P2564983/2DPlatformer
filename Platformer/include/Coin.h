#pragma once

/*!
\file Coin.h
*/

#include <Box2D/Box2D.h>
#include <SFML/Graphics.hpp>

#include "PhysicalThing.h"

using namespace sf;

/*! \class Coin
\brief A collectible coin which cannot move or rotate but player can collide with
*/

class Coin : public PhysicalThing
{
private:
	CircleShape m_shape;
	const float m_radius = 0.2f;

	bool m_collected = false;

public:
	Coin(b2World* world, const sf::Vector2f& position); //!< Complete contructor

	void draw(RenderTarget& target, RenderStates states) const; //!< Overriden function
	void update(); // Checks if coin has been collected

	bool isCollected() { return m_collected; }

	// Abstract method overide:
	void startCollision(b2Fixture* thisFixture, b2Fixture* collidedWith);
	void endCollision(b2Fixture* thisFixture, b2Fixture* collidedWith) {}; // No implementation
};