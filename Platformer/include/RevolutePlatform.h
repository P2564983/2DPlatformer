#pragma once

/*!
\file RevolutePlatform.h
*/

#include <Box2D/Box2D.h>
#include <SFML/Graphics.hpp>

#include "World.h"
#include "Platform.h"

/*! \class RevolutePlatform
\brief A platform with a revolute joint at its centre
*/

class RevolutePlatform : public Platform
{
private:
	b2Body* bodyA; // Thing that will rotate
	b2Body* m_bodyB; // Anchor/hinge
	b2RevoluteJoint* m_joint;

public:
	RevolutePlatform(b2World* world,
		Vector2f& position = Vector2f(0, 0),
		Vector2f& size = Vector2f(5.0f, 0.4f),
		const Color colour = Color::Blue
	); //!< Complete contructor with default parameters
	~RevolutePlatform();

	// Update() and Draw() handled by parent Platform class
};