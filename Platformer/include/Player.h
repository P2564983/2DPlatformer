#pragma once

/*!
\file Player.h
*/

#include "SFMLDebugDraw.h"

#include <Box2D/Box2D.h>
#include <SFML/Graphics.hpp>

#include "PhysicalThing.h"

/*! \class Player
\brief A controllable character in the world
*/

using namespace sf;

class Player : public PhysicalThing, public Drawable
{
private:
	float m_speed;		// Player movement speed
	CircleShape m_shape;	// The drawable object

public:
	Player(b2World* world, const sf::Vector2f& position);
	
	// Player movement
	void move(const b2Vec2& direction);
	void increaseSpeed(const float amount);

	const Vector2f getPosition() const;

	void update();
	void draw(RenderTarget& target, RenderStates states)const ;
};