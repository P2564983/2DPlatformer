#pragma once

/*!
\file Coin.h
*/

#include <Box2D/Box2D.h>
#include <SFML/Graphics.hpp>

#include "PhysicalThing.h"
#include "World.h"

using namespace sf;

/*! \class Coin
\brief A collectible coin which cannot move or rotate but player can collide with
*/

class Coin : public PhysicalThing, public Drawable
{
private:
	CircleShape m_shape;
	const float m_radius = 0.16f;
	int collisionContacts;

	bool toDestroy = false;

public:
	Coin(b2World* world, const sf::Vector2f& position); //!< Complete contructor
	~Coin();

	void draw(RenderTarget& target, RenderStates states) const; //!< Overriden function

	void setUserData(); // overide base function // consider: making PhysicalThing::setUserData() a pure virtual function
	bool destroy();
	b2Body* getBody() { return m_body; }

	void onContact();
	void onSeperation();
};