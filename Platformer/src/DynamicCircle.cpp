/*!
\file dynamicCircle.cpp
*/

#include "DynamicCircle.h"


DynamicCircle::DynamicCircle(b2World * world, const sf::Vector2f& position, const float radius, const float orientation, CollisionFilter type)
{
	b2BodyDef l_bodyDef;
	b2CircleShape l_shape;
	b2FixtureDef l_fixtureDef;


	l_bodyDef.type = b2_dynamicBody;
	l_bodyDef.position.Set(position.x, position.y);
	l_bodyDef.angle = orientation * DEG2RAD;
	m_body = world->CreateBody(&l_bodyDef);

	l_shape.m_radius = radius;

	l_fixtureDef.density = mk_fDensity;
	l_fixtureDef.friction = mk_fFriction;
	l_fixtureDef.restitution = mk_fRestitution;
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
	setRadius(radius);
	setOrigin(radius, radius);
	setRotation(orientation);
	setFillColor(sf::Color::Blue);
}

void DynamicCircle::update()
{
	b2Vec2 pos = m_body->GetPosition();
	setPosition(pos.x, pos.y);

	float angle = m_body->GetAngle()* RAD2DEG;
	setRotation(angle);
}

void DynamicCircle::draw(sf::RenderTarget & target, sf::RenderStates states) const
{
	target.draw((sf::CircleShape)*this); // Draw the Circle Shape

	// Add a line
	sf::RectangleShape line(sf::Vector2f(getRadius(), 0.01f));
	line.setPosition(getPosition());
	line.setOrigin(0.f, 0.005f);
	line.rotate(getRotation());
	target.draw(line);
}


