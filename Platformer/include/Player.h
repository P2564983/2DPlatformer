#pragma once

/*!
\file Player.h
*/

#include "SFMLDebugDraw.h"

#include <Box2D/Box2D.h>
#include <SFML/Graphics.hpp>
#include <set>

#include "PhysicalThing.h"
#include "World.h"
#include "Enemy.h"

/*! \class Player
\brief A controllable character in the world
*/

using namespace sf;

class Player : public PhysicalThing
{
private:
	const float playerRadiusSize = 0.25f;

	float m_speed;			// Player movement speed
	CircleShape m_shape;	// The drawable object
	bool m_isDead = false;

	float m_density = 1.0f;			// density * area = mass
	float m_friction = 0.4f;		// 0 = completely frictionless ; 1 = max friction
	float m_restitution = 0.0f;		// 0 = No Bounce; 1 = completely bouncy

	set<b2Fixture*> platformBeneath;
	b2Fixture* m_lastPlatform;

	int enemyCollisionCount = 0; // Used to detect when the player dies

public:
	Player(b2World* world, const sf::Vector2f& position, Color colour);
	
	// Player movement
	void move(const b2Vec2& direction);
	void jump();
	void increaseSpeed(const float amount);

	const b2Vec2 getLinearVelocity() const;

	void update();
	void draw(RenderTarget& target, RenderStates states) const;

	bool isDead() const { return m_isDead; }
	void resetPosition(b2Vec2& position);

	// Abstract method overide:
	void startCollision(b2Fixture* thisFixture, b2Fixture* collidedWith);
	void endCollision(b2Fixture* thisFixture, b2Fixture* collidedWith);
};