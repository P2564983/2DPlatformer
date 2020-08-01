#pragma once

/*!
\file Player.h
*/

#include "SFMLDebugDraw.h"

#include <Box2D/Box2D.h>
#include <SFML/Graphics.hpp>

#include "PhysicalThing.h"
#include "World.h"

/*! \class Player
\brief A controllable character in the world
*/

using namespace sf;

class Player : public PhysicalThing, public Drawable
{
private:
	float m_speed;			// Player movement speed
	RectangleShape m_shape;	// The drawable object

	float m_density = 1.0f;			// density * area = mass
	float m_friction = 0.4f;		// 0 = completely frictionless ; 1 = max friction
	float m_restitution = 0.0f;		// 0 = No Bounce; 1 = completely bouncy

public:
	Player(b2World* world, const sf::Vector2f& position);
	
	// Player movement
	void move(const b2Vec2& direction);
	void jump();
	void rotateTowards(b2Vec2 target);
	bool rotateTowards(b2Vec2 target, float changeRadians);
	void increaseSpeed(const float amount);

	const Vector2f getPosition() const;

	void update();
	void draw(RenderTarget& target, RenderStates states) const;

	b2Body* getBody() const;	// DELETE THIS METHOD
};