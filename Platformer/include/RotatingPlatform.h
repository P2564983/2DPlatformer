#pragma once

#include <SFML/Graphics.hpp>
#include "PhysicalThing.h"
#include "World.h"

using namespace sf;

class RotatingPlatform : public PhysicalThing
{
private:
	// SFML Shapes
	RectangleShape m_rectangle;	// the platform
	CircleShape m_circle; // the anchor
	// Box2D references
	b2Body* m_anchor;
	b2RevoluteJoint* m_joint;
	// Other properties
	float width = 4.0f;
	float height = 0.4f;
public:
	//RotatingPlatform(b2World* world, sf::Vector2f position, sf::Vector2f size, sf::Vector2f anchor, float orientation, sf::Color colour); // Full constructor

	RotatingPlatform(b2World* world, Vector2f position, Color colour = Color::Cyan);
	void setUserData(void* userData = nullptr);
	void draw(sf::RenderTarget& target, sf::RenderStates states) const; //!< Draw platform
	void update();

	// Abstract method overide
	void startCollision(b2Fixture* thisFixture, b2Fixture* collidedWith) {}; // don't care what collides with me
	void endCollision(b2Fixture* thisFixture, b2Fixture* collidedWith) {};

};
