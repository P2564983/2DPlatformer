#pragma once

/*!
\file PhysicalThing.h
*/

#include <Box2D/Box2D.h>

#define DEG2RAD 0.017453f
#define RAD2DEG 57.29577f

/*!
\class PhysicalThing
\brief A simple class with common attributes and a few const values used in a few places. 
*/
class PhysicalThing 
{
protected:
	b2Body * m_body = nullptr; //!< Box2D body, no need to delete this as BOX2D will look after it
	const float mk_fDensity = 1.0f; //!< Density of the material - used to give mass (how heavy it is in relation to its area)
	const float mk_fFriction = 0.4f; //!< Friction - I guess this is only friction from movement, not when static (how slippery it is)
	const float mk_fRestitution = 0.6f; //1< Restitution - bouncyness of stuff (how bouncy the fixture is)

public:
	enum CollisionFilter 
	{
		ONE = 1,
		TWO = 2,
		FOUR = 4,
		EIGHT = 8,
		SIXTEEN = 16
	}; //!< Enums for collision filtering

	void setUserData(void* data); //!< Set the userdata of the body
};
