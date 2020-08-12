#pragma once

/*!
\file WorldGenerator.h
*/

#include "World.h"
#include "Platform.h"
#include "CoinPlatform.h"
#include "EnemyPlatform.h"
#include "RevolutePlatform.h"
#include "Player.h"

/*! \class WorldGenerator
\brief A class that handles the game world.
This class can create and destory objects as well as render the world.
*/
class WorldGenerator : public PhysicalThing
{
private:
	// Box2D:
	b2World* m_b2World; //!< A reference to the Box2D Physics world used to add and remove things from the world	
	b2Fixture* m_creatorSensor; //!< The sensor fixture used to detect when to create
	b2Fixture* m_destructorSensor; //!< The sensor fixture used to detect when to destroy
	b2Fixture* m_groundSensor; //!< The sensor fixture used to detect when the player falls

	// SFML
	Vector2f m_viewSize; //!< The size of the view used to determine where objects can be created
	float minYPosition; //!< Min y position for platforms to be generated at
	float maxYPosition; //!< Max y position for platforms to be generated at
	float centreYPosition; //!< Center y position of the view

	// World properties:
	Player* m_player;	//!< A reference to the player required to know player state
	set<PhysicalThing*> m_worldObjects; //!< A unique list of everything in the world - this set is updated as objects are created and destroyed
	set<PhysicalThing*> m_toDestroy; //!< A queue of items that need to be destroyed

	Vector2f lastPlatPos; //!< The position of the last generated platform used to determine the position of the next platform to be generated
	bool needToGenerate = false; //!< flag to determine wheter a platform needs be generated

	// Other properties
	float m_speed = 2.0f; //!< speed the view chases the player for an inertia style effect
	float minPlatWidth = 4.0f; //!< The minimum width of a platform to be generated
	float maxPlatWidth = 8.0f; //!< The maximum width of a platform to be generated
	float minPlatHeight = 0.4f; //!< The minimum height of a platform to be generated
	float maxPlatHeight = 0.6f; //!< The maximum height of a platform to be generated
	float minPaddingX = 1.0f; //!< The minimum space between a generated platform and the previous platform 
	float maxPaddingX = 2.0f; //!< The maximum space between a generated platform and the previous platform 

	/*!
	  \brief Helper method to generate a platform
	  \param platType The type of platform to generate
	*/
	void generatePlatform(PlatformType platType);

	/*!
	  \brief Helper method to reset the world (called when a player dies)
	*/
	void resetWorld();

public:
	/*!
	  \brief Default constructor - Creates a world generator
	  \param world A reference to the Box2D world
	  \param view A Reference to the view used to render the world
	*/
	WorldGenerator(b2World* world, View& view);

	/*!
	  \brief Destructor to delete the player and platforms this class generates
	*/
	~WorldGenerator();

	/*!
	  \brief Update the generated world
	  This method will 1. Check of the player is still alive and reset the world if it has dies, 
	  2. Destroy and objects that have gone out of view, 
	  3. Generate platforms just outside of the view so the player always has a platform to move to
	*/
	void update();

	/*!
	  \brief Draw the World to render context
	  \param target The target to draw to (usually the window)
	  \param states The states used for drawing to a RenderTarget
	*/
	void draw(RenderTarget& target, RenderStates states) const; //!< Overide base function to allow drawing of World

	/*!
	  \brief Virtual inherited method called when the World Generator collides with another fixture
	  \param thisFixture the fixture that was involved in the collision (there are three World Generator fixtures: creator, destory and ground)
	  \param collidedWith the fixture this World Generator collided with
	  \see endCollision
	*/
	void startCollision(b2Fixture* whatFixture, b2Fixture* collisionStartedWith);

	/*!
	  \brief Virtual inherited method called when the World Generator ends collision with another fixture
	  \param thisFixture the fixture that was involved in the collision (there are three World Generator fixtures: creator, destory and ground)
	  \param collidedWith the fixture this World Generator ended collision with
	  \see startCollision
	*/
	void endCollision(b2Fixture* whatFixture, b2Fixture* collisionEndedWith);


	/*!
	  \brief Returns a reference to the player
	  \return A reference pointer to the player
	*/
	Player* getPlayer() { return m_player; }
};