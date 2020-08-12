#pragma once

/*!
\file PhysicalThing.h
*/

#include "World.h"

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
	const float mk_fFriction = 0.0f; //!< Friction - I guess this is only friction from movement, not when static (how slippery it is)
	const float mk_fRestitution = 0.0f; //1< Restitution - bouncyness of stuff (how bouncy the fixture is)

public:
	/*!
	  \brief Virtual Destructor that destorys the body attached to this object. Virtual destructor first calls base class destructor where applicable.
	*/
	virtual ~PhysicalThing();

	/*!
	  \brief Sets the Box2D bodies user data
	  \param data the value to assign to the user data, if null this method will set a suitable value.
	*/
	void setUserData(void* data = nullptr); //!< Set the userdata of the body

	/*!
	  \brief Returns the position of the body as a b2Vec2
	  \return Returns the position of the body as a b2Vec2
	*/
	b2Vec2 getPositionB2() const;

	/*!
	  \brief Returns the position of the body as a Vector2f
	  \return Returns the position of the body as a Vector2f
	*/
	Vector2f getPositionV2F() const;

	/*!
	  \brief A physical thing may be updated and drawn - virtual method means derived class function is called
	*/
	virtual void update() {};

	/*!
	  \brief A physical object must be drawable (pass on Pure Virtual Function to derived clases)
	  \param target the target to draw to (usually the window)
	  \param states the states used for drawing to a RenderTarget
	*/
	virtual void draw(RenderTarget& target, RenderStates states) const = 0;

	/*!
	  \brief A physical object may be invloved in a collision (but does not have to be)
	  \param thisFixture the fixture that was involved in the collision
	  \param collidedWith the fixture this object collided with
	  \see endCollision
	*/
	virtual void startCollision(b2Fixture* thisFixture, b2Fixture* collidedWith) {};

	/*!
	  \brief A physical object may be invloved in a collision (but does not have to be)
	  \param thisFixture the fixture that was involved in the collision
	  \param collidedWith the fixture this object collided with
	  \see startCollision
	*/
	virtual void endCollision(b2Fixture* thisFixture, b2Fixture* collidedWith) {};
};
