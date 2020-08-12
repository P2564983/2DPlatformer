#pragma once

/*!
\file Enemy.h
*/

#include <Box2D/Box2D.h>
#include <SFML/Graphics.hpp>

#include "PhysicalThing.h"
#include "World.h"
#include "Platform.h"

/*! \class Player
\brief An enemy that patrols a platform
*/

class Enemy : public PhysicalThing
{
private:
	const b2Vec2 enemyHalfSize = b2Vec2(0.25f, 0.25f);
	const b2Vec2 sensorHalfSize = b2Vec2(enemyHalfSize.x * 0.9f, enemyHalfSize.y * 0.1f); // head sensor

	float m_velocity;			// Enemy velocity (+ value means moving right; - left)
	RectangleShape m_enemyShape;	// The drawable object
	b2Fixture* m_headSensorFixture;
	bool m_isDead = false;

	Platform* m_platform; // the platform this enemy is patrolling

public:
	Enemy(b2World* world, Platform* platformOn, Color colour = Color::Red);
	~Enemy();

	// Enemy movement
	void move();

	void update();
	void draw(RenderTarget& target, RenderStates states) const;
	bool isDead() const;

	// Abstract method overide
	void startCollision(b2Fixture* thisFixture, b2Fixture* collidedWith);
	void endCollision(b2Fixture* thisFixture, b2Fixture* collidedWith) {};
};