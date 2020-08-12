#pragma once

/*!
\file CoinPlatform.h
*/

#include <Box2D/Box2D.h>
#include <SFML/Graphics.hpp>

#include "World.h"
#include "Platform.h"
#include "Coin.h"

/*! \class CoinPlatform
\brief A platform with coins on it which cannot move or rotate but can collide with stuff
*/

class CoinPlatform : public Platform
{
private:
	set<Coin*> m_coins;

public:
	CoinPlatform(b2World* world,
		Vector2f& position = Vector2f(0, 0),
		Vector2f& size = Vector2f(5.0f, 0.4f),
		const Color colour = Color::Green
	); //!< Complete contructor with default parameters
	~CoinPlatform();

	void update(); //!< Update platform attributes (e.g. Size, position, colour)
	void draw(RenderTarget& target, RenderStates states) const; //!< Overide base function to allow drawing of Platform objects
};