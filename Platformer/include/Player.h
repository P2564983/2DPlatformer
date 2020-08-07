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

/*! \class Player
\brief A controllable character in the world
*/

using namespace sf;

class Player : public PhysicalThing, public Drawable
{
private:
	const b2Vec2 playerHalfSize = b2Vec2(0.25f, 0.25f);
	const b2Vec2 sensorHalfSize = b2Vec2(playerHalfSize.x * 0.75f, playerHalfSize.y * 0.1f);

	float m_speed;			// Player movement speed
	RectangleShape m_shape;	// The drawable object
	b2Fixture* groundSensorFixture;

	float m_density = 1.0f;			// density * area = mass
	float m_friction = 0.4f;		// 0 = completely frictionless ; 1 = max friction
	float m_restitution = 0.0f;		// 0 = No Bounce; 1 = completely bouncy

	set<b2Fixture*> platformBeneath;

public:
	Player(b2World* world, const sf::Vector2f& position, Color colour);
	
	// Player movement
	void move(const b2Vec2& direction);
	void jump();
	void rotateTowards(b2Vec2 target);
	bool rotateTowards(b2Vec2 target, float changeRadians);
	void increaseSpeed(const float amount);

	const Vector2f getPosition() const;
	void registerGroundContact(const bool hasCollided, b2Fixture* fixture);

	void update();
	void draw(RenderTarget& target, RenderStates states) const;
	void setUserData();

	// Debug Stuff = DELETE/REMOVE
	b2Body* getBody() const;
	b2Vec2 jumpStart;
	b2Vec2 jumpHighest;
	b2Vec2 velHigh;
	int jumpCounter = 0;
	int jumpVelCounter = 0;
	int jumpPosCounter = 0;
	int jumpDebug = 0;
};