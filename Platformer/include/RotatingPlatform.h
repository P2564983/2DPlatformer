#pragma once

#include <SFML/Graphics.hpp>
#include "PhysicalThing.h"

using namespace sf;

class RotatingPlatform : public PhysicalThing, public sf::Drawable
{
private:
	// SFML Shapes
	RectangleShape m_rectangle;	// the platform
	CircleShape m_circle; // the anchor
	// Box2D references
	b2Body* m_anchor;
	b2RevoluteJoint* m_joint;
	// Other properties
	float width = 2.0f;
	float height = 0.4f;
public:
	//RotatingPlatform(b2World* world, sf::Vector2f position, sf::Vector2f size, sf::Vector2f anchor, float orientation, sf::Color colour); // Full constructor

	RotatingPlatform(b2World* world, Vector2f position, Color colour);
	void draw(sf::RenderTarget& target, sf::RenderStates states) const; //!< Draw platform
	void update();
};
