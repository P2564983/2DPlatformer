#pragma once

/*!
\file PhysicalThing.h
*/

#include "World.h"
#include "SFML/Graphics.hpp"

#define DEG2RAD 0.017453f
#define RAD2DEG 57.29577f

/*!
\class PhysicalThing
\brief A simple class with common attributes and a few const values used in a few places. 
*/
class PhysicalThing : public Drawable
{
protected:
	b2Body * m_body = nullptr; //!< Box2D body, no need to delete this as BOX2D will look after it
	const float mk_fDensity = 1.0f; //!< Density of the material - used to give mass (how heavy it is in relation to its area)
	const float mk_fFriction = 0.4f; //!< Friction - I guess this is only friction from movement, not when static (how slippery it is)
	const float mk_fRestitution = 0.6f; //1< Restitution - bouncyness of stuff (how bouncy the fixture is)

public:
	virtual ~PhysicalThing();

	void setUserData(void* data = nullptr); //!< Set the userdata of the body

	// Misc
	b2Vec2 getPositionB2() const;
	Vector2f getPositionV2F() const;

	// A physical thing may be updated and drawn - virtual method means derived class function is called:
	virtual void update() {};

	// A physical objects must be drawable (pass on Pure Virtual Function to derived clases):
	virtual void draw(RenderTarget& target, RenderStates states) const = 0;

	// A physical thing can be involved in collision (but does not have to be):
	virtual void startCollision(b2Fixture* thisFixture, b2Fixture* collidedWith) {};
	virtual void endCollision(b2Fixture* thisFixture, b2Fixture* collidedWith) {};
};
