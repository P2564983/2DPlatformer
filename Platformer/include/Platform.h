#pragma once

/*!
\file Platform.h
*/

#include <Box2D/Box2D.h>
#include <SFML/Graphics.hpp>

#include "PhysicalThing.h"
#include "World.h"

/*! \class Platform
\brief A platform which cannot move or rotate but can collide with stuff
*/

using namespace sf;

class Platform : public PhysicalThing
{
protected:
	RectangleShape m_shape;
	Vector2f m_size;

	b2Fixture* platformStartSensor;
	b2Fixture* platformEndSensor;

public:
	Platform(b2World* world, 
		Vector2f& position = Vector2f(0, 0), 
		Vector2f& size = Vector2f(4.0f, 0.4f), 
		const Color colour = Color::Green
	); //!< Complete contructor with default parameters
	virtual ~Platform();

	// Virtual function to ensure derived classes methods are called
	virtual void update(); //!< Update platform attributes (e.g. Size, position, colour);
	virtual void draw(RenderTarget& target, RenderStates states) const; //!< Overide base function to allow drawing of Platform objects

	// Abstract method overide
	void startCollision(b2Fixture* thisFixture, b2Fixture* collidedWith) {}; // don't care what collides with me
	void endCollision(b2Fixture* thisFixture, b2Fixture* collidedWith) {};

	Vector2f getSize() const;
};