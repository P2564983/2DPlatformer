#pragma once

/*!
\file Player.h
*/

#include "World.h"
#include "PhysicalThing.h"
#include "Platform.h"

/*! \class Player
\brief A controllable character in the world
*/
class Player : public PhysicalThing
{
private:
	const float playerRadiusSize = 0.25f; //!< The players size

	float m_speed;	//!< Player movement speed - this gradually increases as the game progress'
	CircleShape m_shape; //!< The drawable player
	bool m_isDead = false; //!< Flag indicating the state of player

	set<b2Fixture*> platformBeneath; //!< A list of platforms beneath the player
	b2Fixture* m_lastPlatform; //!< The last platform the player collided with (used to determine when the player lands on a new platform)

	int enemyCollisionCount = 0; //!< Used to detect when the player dies by its collision count with an enemy

	Color m_airColour; //!< The player colour when in the air
	Color m_groundColour; //!< The player colour when grounded

public:
	/*!
	  \brief Default constructor
	  \param world The Box2D world that this player is in
	  \param position The position of the player in the world
	  \param airColour The colour of this player when it is in the air
	  \param groundColour The colour of this player when it is grounded
	*/
	Player(b2World* world, const sf::Vector2f& position, Color airColour, Color groundColour);

	/*!
	  \brief Move the player in a given x-direction
	  \param direction the direction to move the player in
	*/
	void move(const float direction);

	/*!
	  \brief Function to make the player jump (jump is only possible when the player is grounded)]
	*/
	void jump();

	/*!
	  \brief Update the players speed based on game time and check if whether the player is dead
	*/
	void update();

	/*!
	  \brief Draw the player to render context
	  \param target The target to draw to (usually the window)
	  \param states The states used for drawing to a RenderTarget
	*/
	void draw(RenderTarget& target, RenderStates states) const;

	/*!
	  \brief Returns the state of the player
	  \return A boolean indicating whether the player is alive (true) or dead (false)
	*/
	bool isDead() const { return m_isDead; }

	/*!
	  \brief Reset the player to a given position - this method only executes completely when the player is dead
	  \see isDead
	*/
	void resetPosition(b2Vec2& position);

	/*!
	  \brief Virtual inherited method called when this player collides with another fixture
	  \param thisFixture the platform fixture that was involved in the collision (there is only one player fixture)
	  \param collidedWith the fixture this enemy collided with
	  \see endCollision
	*/
	void startCollision(b2Fixture* thisFixture, b2Fixture* collidedWith);

	/*!
	  \brief Virtual inherited method called when this player ends collision with another fixture
	  \param thisFixture the player fixture that was involved in the collision (there is only one player fixture)
	  \param collidedWith the fixture this enemy ended collision with
	  \see startCollision
	*/
	void endCollision(b2Fixture* thisFixture, b2Fixture* collidedWith);
};