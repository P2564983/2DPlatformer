#pragma once

/*!
\file WorldGenerator.h
*/

#include <Box2D/Box2D.h>
#include <SFML/Graphics.hpp>
#include <set>
#include <vector>

#include "World.h"
#include "Platform.h"
#include "RotatingPlatform.h"
#include "CoinPlatform.h"
#include "EnemyPlatform.h"
#include "RevolutePlatform.h"
#include "Player.h"
#include "Coin.h"

/* \struct MyWorld
\brief A structure that contains all the world objects
*/
struct MyWorld
{
	Player* player; //!< The controllable actor in this world
	set<Platform*> platforms; //!< A unique set of all the platforms in this world
	set<RotatingPlatform*> rotatingPlatforms; //!< A unique set of all the rotating platforms in this world
	set<CoinPlatform*> coinPlatforms; //!< A unique set of all the rotating platforms in this world
	set<EnemyPlatform*> enemyPlatforms; //!< A unique set of all the platforms with enemies in this world
};

/* \struct WorldSettings
\brief A structure that contains settings for a WorldGenerator
*/
struct WorldSettings
{
	b2World* b2World;
	View* renderView;
};

/*! \class WorldGenerator
\brief A class that handles the game world.
This class can create and destory objects as well as render the world.
*/
class WorldGenerator : public PhysicalThing
{
private:
	// Box2D:
	b2World* m_b2World; // used to add and remove things from the physics world	
	b2Fixture* m_creatorSensor; //!< The sensor fixture used to detect when to create
	b2Fixture* m_destructorSensor; //!< The sensor fixture used to detect when to destroy
	b2Fixture* m_groundSensor; //!< The sensor fixture used to detect when the player falls

	// SFML
	Vector2f m_viewSize; //!< The size of the view used to determine where objects can be created
	
	// World properties:
	Player* m_player;	// to know where the player is:
	set<PhysicalThing*> m_worldObjects; // Everything in the world - this set is updated as objects are created and destroyed
	set<PhysicalThing*> m_toDestroy; // A queue of items that need to be destroyed

	Vector2f lastPlatPos; // helper to determine where a platform should be placed:
	bool needToGenerate = false;	// flag to determine wheter a platform need be generated

	// Other properties
	float m_speed = 2.0f; // speed the view chases the player for an inertia style effect
	float minYPosition, maxYPosition, centreYPosition; // min, max and centre positions for generated platforms
	float minPlatWidth = 4.0f, maxPlatWidth = 8.0f; // Keep these numbers above 1
	float minPlatHeight = 0.4f, maxPlatHeight = 0.6f; // Keep these numbers below 1
	float minPaddingX = 1.0f, maxPaddingX = 2.0f;

	void generatePlatform(PlatformType platType);
	void resetWorld();

public:
	WorldGenerator(b2World* world, View& view);
	~WorldGenerator();
	void update();

	// Abstract class overide
	void startCollision(b2Fixture* whatFixture, b2Fixture* collisionStartedWith);
	void endCollision(b2Fixture* whatFixture, b2Fixture* collisionEndedWith);

	void draw(RenderTarget& target, RenderStates states) const; //!< Overide base function to allow drawing of World

	Player* getPlayer() { return m_player; }
};