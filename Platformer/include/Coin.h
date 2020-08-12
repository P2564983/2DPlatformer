#pragma once

/*!
\file Coin.h
*/

#include "PhysicalThing.h"

/*! \class Coin
\brief A collectible coin which cannot move or rotate but player can collide with
*/

class Coin : public PhysicalThing
{
private:
	CircleShape m_shape; //!< The renderable shape
	const float m_radius = 0.2f; //!< Size of coin
	bool m_collected = false; //!< Flag to determine when this coin has been collected

public:
	/*!
	  \brief Default constructor
	  \param world The Box2D world that this platform is in
	  \param position The position of this coin in the world
	*/
	Coin(b2World* world, const sf::Vector2f& position);

	/*!
	  \brief Checks if coin has been collected and stops rendering it if it has
	*/
	void update();

	/*!
	  \brief Draws this coin
	  \param target the target to draw to (usually the window)
	  \param states the states used for drawing to a RenderTarget
	*/
	void draw(RenderTarget& target, RenderStates states) const;

	/*!
	  \brief Checks whether the coins has been collected
	  \return Boolean indicating whether the coin has been collected
	*/
	bool isCollected() { return m_collected; }

	/*!
	  \brief Virtual inherited method called when this coin collides with another fixture
	  \param thisFixture the coin fixture that was involved in the collision (there is only one fixture on a coin)
	  \param collidedWith the fixture this coin collided with
	*/
	void startCollision(b2Fixture* thisFixture, b2Fixture* collidedWith);

	/*!
	  \brief Virtual inherited method called when this coin ends collision with another fixture. This method is not implemented (as there is no need).
	  \param thisFixture the coin fixture that was involved in the collision (there is only one fixture on a coin)
	  \param collidedWith the fixture this coin collided with
	*/
	void endCollision(b2Fixture* thisFixture, b2Fixture* collidedWith) {};
};