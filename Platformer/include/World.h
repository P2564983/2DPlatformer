#pragma once

/*!
\file World.h
*/

#include <Box2D/Box2D.h>
#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include <set>

using namespace std;
using namespace sf;

#define DEGTORAD	0.0174532925199432957f
#define RADTODEG	57.295779513082320876f
#define PI			3.141592654

#define B2UP	b2Vec2(0.f, -1.f)
#define B2DOWN	b2Vec2(0.f, 1.f)
#define B2LEFT	b2Vec2(-1.f, 0.f)
#define B2RIGHT	b2Vec2(1.f, 0.f)

const static float zoomInFactor = 0.9f; //!< Factor value used when the mouse scroll is zoomed in
const static float zoomOutFactor = 1.f / zoomInFactor; //!< Factor value used when the mouse scroll is zoomed out

/*! \struct Score
\brief A (static) struct which maintains the current and high score as well as time elasped of the game being played
*/
struct Score
{
private:
	static unsigned int currentScore; //<! The current score as a static unsgined integer
	static unsigned int highScore; //<! The high score as a static unsigned integer
	static Clock gameTime; //!< A clock to determine how much time has elapsed since the game started

	/*!
	  \brief Default constructor made private to prevent initialisation of this struct (as this struct is static)
	*/
	Score();

public:
	/*!
	  \brief Increment the current score counter - this function also checks if the current score is now the high score
	  \param scoreChange the value to increment the current score by
	  \see getCurrentScore, getHighScore
	*/
	static void addToScore(const unsigned int scoreChange);

	/*!
	  \brief Resets the current score and game time - essentially starting a new game
	*/
	static void resetCurrentScore();

	/*!
	  \brief Returns the current score
	  \return the current score
	*/
	static unsigned int getCurrentScore() { return currentScore; }

	/*!
	  \brief Returns the highest score
	  \return the highest score
	*/
	static unsigned int getHighScore() { return highScore; }

	/*!
	  \brief Returns the current game time
	  \return the highest score
	  \see getGameTimeAsSeconds
	*/
	static Time getGameTime() { return gameTime.getElapsedTime(); }

	/*!
	  \brief Returns the current game time in seconds
	  \return a floating point indicating how much time has passed since score reset
	*/
	static float getGameTimeAsSeconds() { return gameTime.getElapsedTime().asSeconds(); }
};

/*! \enum FixtureType
	\brief an enum representing fixture type - usually assigned to a fixture's user data
*/
enum class FixtureType
{
	Undefined = 0,
	Sensor,
	Player,
	Enemy,
	Platform,
	RotatingPlatform,
	Hinge
};

/*! \enum PlatformType
	\brief an enum representing platform type - used for random platform generation
*/
enum class PlatformType
{
	Normal = 0,
	Coin,
	Enemy,
	Revolute,
	Count // KEEP THIS LAST
};

/*! \enum SensorType
	\brief an enum representing sensor type - this is set as a fixtures user data when the fixture is a sensor
*/
enum class SensorType
{
	Undefined = 0,
	PlatformStart,
	PlatformEnd,
	//PlayerFoot,
	EnemyHead,
	WorldCreator,
	WorldDestructor,
	WorldGround
};

/*! \enum CollisionFilter
	\brief an enum representing different collision types - this is used for both the filter and category
*/
enum class CollisionFilter
{
	// Can go up to 1<<16 = 1000000000000000
	Nothing =		0,
	Something =		1<<0,
	Player =		1<<1,
	Enemy =			1<<2,
	Collectible =	1<<3,
	Platform =		1<<4,
	Everything =	0xFFFF
};