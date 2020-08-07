#pragma once

/*!
\file WorldGenerator.h
*/

#include <Box2D/Box2D.h>
#include <SFML/Graphics.hpp>
#include <set>

#include "World.h"
#include "Platform.h"

/*! \class WorldGenerator
\brief A class that handles the game world.
This class can create and destory objects as well as render the world.
*/
class WorldGenerator
{
private:
	b2World* m_world; // used to add and remove things from the physics world
	b2Body* m_body; // A physics body attached to the world itself
	b2Fixture* m_creatorFixture;	//!< The fixture used to detect when to create
	b2Fixture* m_destructorFixture; //!< The fixture used to detect when to destroy
	set<Platform*> m_platforms;	//!< A complete set of all the platforms in the world

	float m_speed = 1.0f;

public:
	WorldGenerator(b2World* world, View& view);
	void setUserData(void* userData = nullptr);
	void update(View& view);
	void onAction(b2Fixture* whatFixture, b2Fixture* collissionStartedWith);
	void offAction(b2Fixture* whatFixture, b2Fixture* collisionEndedWith);

	static set<Platform*> m_platToDestory; // should really be private
};