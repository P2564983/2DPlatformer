#pragma once

/*!
\file Platform.h
*/

#include "World.h"
#include "PhysicalThing.h"

/*! \class Platform
\brief A platform which cannot move or rotate but can collide with stuff
*/
class Platform : public PhysicalThing
{
protected:
	RectangleShape m_shape; //!< The renderable object
	Vector2f m_size; //!< Platform dimensions

	b2Fixture* platformStartSensor; //!< A fixture sensor placed at the platform start
	b2Fixture* platformEndSensor; //!< A fixture sensor placed at the platform end

public:
	/*!
	  \brief Default constructor
	  \param world The Box2D world that this platform is in
	  \param position The position of the platform in the world (default value: (0, 0))
	  \param size the The size of the platform in the world (default value: (4, 0.4))
	  \param colour The colour of this platform (default value: Green)
	*/
	Platform(b2World* world, Vector2f& position = Vector2f(0, 0), Vector2f& size = Vector2f(4.0f, 0.4f), const Color colour = Color::Green);

	/*!
	  \brief Virtual destructor which calls base class destructor where applicable and then nullifies platform start and end fixtures
	*/
	virtual ~Platform();

	/*!
	  \brief Update the platform - virtual function ensures derived class' update method is called if implemented
	*/
	virtual void update(); //!< Update platform attributes (e.g. Size, position, colour);

	/*!
	  \brief Draw the platform to render context - virtual function ensures derived class' draw method is called if implemented
	  \param target The target to draw to (usually the window)
	  \param states The states used for drawing to a RenderTarget
	*/
	virtual void draw(RenderTarget& target, RenderStates states) const; //!< Overide base function to allow drawing of Platform objects

	/*!
	  \brief Virtual inherited method called when this platform collides with another fixture
	  \param thisFixture the platform fixture that was involved in the collision (there are three platform fixtures; the main body, start sensor and end sensor)
	  \param collidedWith the fixture this enemy collided with
	  \see endCollision
	*/
	void startCollision(b2Fixture* thisFixture, b2Fixture* collidedWith) {};

	/*!
	  \brief Virtual inherited method called when this platform ends collision with another fixture
	  \param thisFixture the platform fixture that was involved in the collision (there are three platform fixtures; the main body, start sensor and end sensor)
	  \param collidedWith the fixture this enemy ended collision with
	  \see startCollision
	*/
	void endCollision(b2Fixture* thisFixture, b2Fixture* collidedWith) {};
};