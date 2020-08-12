#pragma once

/*!
\file EnemyPlatform.h
*/

#include "World.h"
#include "Platform.h"
#include "Enemy.h"

/*! \class EnemyPlatform
\brief A platform which generates an enemy on it
*/
class EnemyPlatform : public Platform
{
private:
	Enemy* m_enemy; //!< The enemy game object generated on to this platform

public:
	/*!
	  \brief Default constructor
	  \param world The Box2D world that this enemy is in
	  \param position The position of the platform in the world (default value: (0, 0))
	  \param size the The size of the platform in the world (default value: (10, 0.4))
	  \param colour The colour of this platform (default value: Green)
	*/
	EnemyPlatform(b2World* world, Vector2f& position = Vector2f(0, 0), Vector2f& size = Vector2f(10.0f, 0.4f), const Color colour = Color(75, 10, 90));

	/*!
	  \brief Destructor which cleans up the generated enemy
	*/
	~EnemyPlatform();

	/*!
	  \brief Update the platform and enemy game objects
	*/
	void update();

	/*!
	  \brief Draw the platform to render context
	  \param target The target to draw to (usually the window)
	  \param states The states used for drawing to a RenderTarget
	*/
	void draw(RenderTarget& target, RenderStates states) const; //!< Overide base function to allow drawing of Platform objects
};