#pragma once

/*!
\file PlayerGroundContactListener.h
*/

#include <Box2D\Box2D.h>

#include "Player.h"
#include "World.h"

/*! \class PlayerGroundContactListener
\brief A listener which listens for contacts between player and ground/anything below
*/

class PlayerGroundContactListener : public b2ContactListener
{
public:
	void BeginContact(b2Contact* contact); //!< Called when two fixtures begin to touch
	void EndContact(b2Contact* contact); //!< Called when two fixtures cease to touch
};