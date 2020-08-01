#include "..\include\Coin.h"
#pragma once

Coin::Coin(b2World* world, const sf::Vector2f& position)
{
	// Body in the Physics world
	b2BodyDef l_bodyDef;
	l_bodyDef.position.Set(position.x, position.y);
	l_bodyDef.angle = 0;
	l_bodyDef.type = b2_staticBody;
	l_bodyDef.type = b2_kinematicBody; // REMOVE
	m_body = world->CreateBody(&l_bodyDef);

	// Box2D Shape
	b2CircleShape l_shape;
	l_shape.m_radius = m_radius;

	// Box2D Fixture
	b2FixtureDef l_fixtureDef;
	l_fixtureDef.density = mk_fDensity;
	l_fixtureDef.friction = mk_fFriction;
	l_fixtureDef.restitution = mk_fRestitution;
	l_fixtureDef.shape = &l_shape;
	m_body->CreateFixture(&l_fixtureDef);

	m_shape.setRadius(m_radius);
	m_shape.setOrigin(m_radius, m_radius);
	m_shape.setPosition(position);
	m_shape.setRotation(0);
	m_shape.setFillColor(Color(255, 223, 0)); // Goldish colour

	// misc
	collisionContacts = 0;
}

Coin::~Coin()
{
	//cout << "Coin Destructor Called" << endl;
	//m_body->GetWorld()->DestroyBody(m_body);
}

void Coin::draw(RenderTarget& target, RenderStates states) const
{
	target.draw(m_shape);	// Draw the coin shape

	// Draw a smaller circle within
	float smallRadius = m_radius * 0.6f;

	CircleShape smallCircle(smallRadius);
	smallCircle.setOrigin(smallRadius, smallRadius);
	smallCircle.setPosition(m_shape.getPosition());
	smallCircle.setFillColor(Color::Red);
	target.draw(smallCircle);
}

void Coin::setUserData()
{
	m_body->SetUserData(new pair<string, void*>(typeid(Coin).name(), this));
}

bool Coin::destroy()
{
	if (!toDestroy) return false;

	m_body->GetWorld()->DestroyBody(m_body);
	return true;
}

void Coin::onContact()
{
	collisionContacts++;
	//m_shape.setFillColor(Color::Blue);
	toDestroy = true;
}

void Coin::onSeperation()
{
	return;
	if (collisionContacts = max(0, collisionContacts - 1));
		m_shape.setFillColor(Color(255, 223, 0)); // Goldish colour
}
