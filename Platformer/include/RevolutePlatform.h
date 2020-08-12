#pragma once

/*!
\file RevolutePlatform.h
*/

#include "World.h"
#include "Platform.h"

/*! \class RevolutePlatform
\brief A platform with a revolute joint at its centre
*/
class RevolutePlatform : public Platform
{
private:
	b2Body* m_anchor; //!< The Anchor of the revolute joint
	b2RevoluteJoint* m_joint; //!< A revolute joint connecting the platform with an anchor

public:
	/*!
	  \brief Default constructor
	  \param world The Box2D world that this platform is in
	  \param position The position of the platform in the world (default value: (0, 0))
	  \param size the The size of the platform in the world (default value: (5, 0.4))
	  \param colour The colour of this platform (default value: Blue)
	*/
	RevolutePlatform(b2World* world, Vector2f& position = Vector2f(0, 0), Vector2f& size = Vector2f(5.0f, 0.4f), const Color colour = Color::Blue);

	/*!
	  \brief Destructor which destorys the anchor body (parent class destroys the platform body)
	*/
	~RevolutePlatform();

	// Update() and Draw() handled by parent Platform class
};