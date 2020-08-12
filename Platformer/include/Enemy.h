#pragma once

/*!
\file Enemy.h
*/

#include "PhysicalThing.h"

/*! \class Enemy
\brief An enemy that patrols a platform
*/
class Enemy : public PhysicalThing
{
private:
	const b2Vec2 enemyHalfSize = b2Vec2(0.25f, 0.25f); //!< The half size of the enemy used to construct its body shape
	const b2Vec2 sensorHalfSize = b2Vec2(enemyHalfSize.x, enemyHalfSize.y * 0.1f); //!< The size of its head sensor

	float m_velocity; //!< Enemy velocity used to determine its speed and direction (+ value means moving right; - left)
	RectangleShape m_enemyShape; //!< The renderable object
	b2Fixture* m_headSensorFixture; //!< A sensor attached to the enemy head used to detect player collision
	bool m_isDead = false; //!< Flag indicating whether the player has killed this enemy

public:
	/*!
	  \brief Default constructor
	  \param world The Box2D world that this enemy is in
	  \param position The position of this enemy in the world (default value: (0, 0))
	  \param colour The colour of this enemy (default value: Red)
	*/
	Enemy(b2World* world, Vector2f position = Vector2f(0, 0), Color colour = Color::Red);

	/*!
	  \brief Destructor cleans up pointer values
	*/
	~Enemy();

	/*!
	  \brief Move the enemy based on its velocity
	*/
	void move();
	
	/*!
	  \brief Update the players position and check if it has been killed
	*/
	void update();

	/*!
	  \brief Draw the enemy to render context
	  \param target the target to draw to (usually the window)
	  \param states the states used for drawing to a RenderTarget
	*/
	void draw(RenderTarget& target, RenderStates states) const;

	/*!
	  \brief Returns the state of the player
	  \return boolean indicating whether the player is alive (true) or dead (false)
	*/
	bool isDead() const;

	/*!
	  \brief Virtual inherited method called when this enemy collides with another fixture
	  \param thisFixture the enemy fixture that was involved in the collision (there are two enemy fixtures; the main body and the head sensor)
	  \param collidedWith the fixture this enemy collided with
	  \see endCollision
	*/
	void startCollision(b2Fixture* thisFixture, b2Fixture* collidedWith);

	/*!
	  \brief Virtual inherited method called when this enemy ends collision with another fixture
	  \param thisFixture the enemy fixture that was involved in the collision (there are two enemy fixtures; the main body and the head sensor)
	  \param collidedWith the fixture this enemy ended collision with
	  \see startCollision
	*/
	void endCollision(b2Fixture* thisFixture, b2Fixture* collidedWith) {};
};