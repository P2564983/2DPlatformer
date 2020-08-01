#pragma once

/*!
\file CoinPlayerContactListener.h
*/

#include <Box2D\Box2D.h>

#include "Player.h"
#include "Coin.h"
#include "World.h"

/*! \class CoinPlayerContactListener
\brief A listener which listens for contacts between player and coins
*/

class CoinPlayerContactListener : public b2ContactListener
{
public:
	void BeginContact(b2Contact* contact); //!< Called when two fixtures begin to touch
	void EndContact(b2Contact* contact); //!< Called when two fixtures cease to touch
};