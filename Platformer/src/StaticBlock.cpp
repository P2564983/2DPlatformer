/*!
\file StaticBlock.cpp
*/

#include "StaticBlock.h"

StaticBlock::StaticBlock(b2World * world, const sf::Vector2f& position, const sf::Vector2f& size, const float& orientation)
{
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
	l_fixtureDef.restitution = mk_fRestitution;
	l_fixtureDef.shape = &l_shape;
	m_body->CreateFixture(&l_fixtureDef);

	setPosition(position);
	setSize(size);
	setOrigin(size * 0.5f);
	setRotation(orientation);
	setFillColor(sf::Color::Green);
	setOutlineThickness(0.f);
}

