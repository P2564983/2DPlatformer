#pragma once

/*!
\file World.h
*/

#include <Box2D/Box2D.h>
#include <SFML/Graphics.hpp>
#include <iostream>
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

const static float zoomInFactor = 0.9f;
const static float zoomOutFactor = 1.f / zoomInFactor;

class Player;

struct Score
{
private:
	static unsigned int currentScore;
	static unsigned int highScore;
	static Clock gameTime;
	Score();

public:
	static void addToScore(const unsigned int scoreChange);
	static void resetCurrentScore();
	// Getters
	static unsigned int getCurrentScore() { return currentScore; }
	static unsigned int getHighScore() { return highScore; }
	static Time getGameTime() { return gameTime.getElapsedTime(); }
	static float getGameTimeAsSeconds() { return gameTime.getElapsedTime().asSeconds(); }
};

enum class FixtureType
{
	Undefined = 0,
	Sensor,
	Player,
	Enemy,
	Platform,
	RotatingPlatform,
	hinge
};

enum class PlatformType
{
	Normal = 0,
	Coin,
	Enemy,
	Revolute,
	Count // LEAVE THIS LAST
};

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