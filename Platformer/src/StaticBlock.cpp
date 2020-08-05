/*!
\file StaticBlock.cpp
*/

#include "StaticBlock.h"

StaticBlock::StaticBlock(b2World* world, const sf::Vector2f& position, const sf::Vector2f& size, const float& orientation, CollisionFilter type)
{
	// Body in the Physics world
	b2BodyDef l_bodyDef;
	l_bodyDef.position.Set(position.x, position.y);
	l_bodyDef.angle = orientation * DEG2RAD;
	m_body = world->CreateBody(&l_bodyDef);

	b2PolygonShape l_shape;
	l_shape.SetAsBox(size.x * 0.5f, size.y * 0.5f);
	l_shape.m_radius = 0.0f;

	b2FixtureDef l_fixtureDef;
	l_fixtureDef.density = mk_fDensity;
	l_fixtureDef.friction = mk_fFriction;
	//l_fixtureDef.restitution = mk_fRestitution;
	l_fixtureDef.restitution = 0; // Static Blocks are not bouncy
	l_fixtureDef.shape = &l_shape;
	// Collision Filtering
	l_fixtureDef.filter.categoryBits = type;
	switch (type)
	{
	default:
	case ONE:
	case TWO:
	case FOUR:
	case EIGHT:
		l_fixtureDef.filter.maskBits = ONE | TWO | FOUR | EIGHT | SIXTEEN; // Collides with everything
		break;
	case SIXTEEN:
		l_fixtureDef.filter.maskBits = SIXTEEN; // Collides with its own type only
		break;
	}
	m_body->CreateFixture(&l_fixtureDef);

	setPosition(position);
	setSize(size);
	setOrigin(size * 0.5f);
	setRotation(orientation);
	setFillColor(sf::Color::Green);
	setOutlineThickness(0.f);
}

