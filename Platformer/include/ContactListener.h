#pragma once

/*!
\file ContactListener.h
*/

#include "World.h"
#include "PhysicalThing.h"

/*! \class ContactListener
\brief A listener which listens for contacts between all fixtures
*/
class ContactListener : public b2ContactListener
{
public:
	/*!
	  \brief A callback function triggered when two fixtures collides
	  \param contact the Box2D contact information regarding the collision - this contains useful information such as what fixtures were involved and where the collision occured
	  \see EndContact
	*/
	void BeginContact(b2Contact* contact);

	/*!
	  \brief A callback function triggered when two fixtures end collision
	  \param contact the Box2D contact information regarding the collision - this contains useful information such as what fixtures were involved and where the collision occured
	  \see BeginContact
	*/
	void EndContact(b2Contact* contact); //!< Called when two fixtures cease to touch
};