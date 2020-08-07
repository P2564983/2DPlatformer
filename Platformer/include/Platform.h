#pragma once

/*!
\file Platform.h
*/

#include <Box2D/Box2D.h>
#include <SFML/Graphics.hpp>

#include "PhysicalThing.h"
#include "World.h"

/*! \class Platform
\brief A platform which can not move or rotate but can collide with stuff
*/

using namespace sf;

class Platform : public Drawable, public PhysicalThing
{
private:
	RectangleShape m_shape;

public:
	Platform(b2World* world, 
		Vector2f& position = Vector2f(0, 0), 
		Vector2f& size = Vector2f(4.0f, 0.4f), 
		const Color colour = Color::Green
	); //!< Complete contructor with default parameters

	void setUserData(void* userData = nullptr);
	void update(); //!< Update platform attributes (e.g. Size, position, colour)
	void draw(RenderTarget& target, RenderStates states) const; //!< Overide base function to allow drawing of Platform objects
};