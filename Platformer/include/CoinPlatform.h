#pragma once

/*!
\file CoinPlatform.h
*/

#include "World.h"
#include "Platform.h"
#include "Coin.h"

/*! \class CoinPlatform
\brief A platform with coins on it which cannot move or rotate but can collide with stuff (namely the player)
*/

class CoinPlatform : public Platform
{
private:
	set<Coin*> m_coins; //!< A unique collection of coins placed on this platform

public:
	/*!
	  \brief Default constructor with some default values
	  \param world The Box2D world that this platform is in
	  \param position The position of this platform in the world
	  \param size The size of this platfrom in the world
	  \param colour The colour of this platform
	*/
	CoinPlatform(b2World* world, Vector2f& position = Vector2f(0, 0), Vector2f& size = Vector2f(5.0f, 0.4f), const Color colour = Color::White); 

	/*!
	  \brief Destructor cleans up all the coins on this platform
	*/
	~CoinPlatform();

	/*!
	  \brief Update platform attributes, namely platform position and coins on this platform
	*/
	void update();

	/*!
	  \brief Draws this coin platform. Calls parent draw function to draw the platform and then draws all the available coins.
	  \param target the target to draw to (usually the window)
	  \param states the states used for drawing to a RenderTarget
	*/
	void draw(RenderTarget& target, RenderStates states) const; //!< Overide base function to allow drawing of Platform objects
};