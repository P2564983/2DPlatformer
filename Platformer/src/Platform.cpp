#include "Platform.h"

Platform::Platform(b2World* world, Vector2f& position, Vector2f& size, const Color colour)
{
	float halfWidth = size.x * 0.5f;
	float halfHeight = size.y * 0.5f;

	// Create the Physics body:
	b2BodyDef l_bodyDef;
	//l_bodyDef.type = b2_dynamicBody; // this body reacts to forces (see below)
	//l_bodyDef.gravityScale = 0; // Body reacts to forces except gravity
	l_bodyDef.type = b2_kinematicBody;
	l_bodyDef.position.Set(position.x, position.y);
	l_bodyDef.angle = 0;
	m_body = world->CreateBody(&l_bodyDef);
	m_body->SetFixedRotation(true); // body cannot rotate

	// Create a physics shape to attach to fixture
	b2PolygonShape l_shape;
	l_shape.SetAsBox(halfWidth, halfHeight);
	l_shape.m_radius = 0;

	// Create a fixture definition:
	b2FixtureDef l_fixtureDef;
	l_fixtureDef.shape = &l_shape;
	l_fixtureDef.density = mk_fDensity;
	l_fixtureDef.friction = mk_fFriction;
	l_fixtureDef.restitution = 0; // not bouncy
	// Attach the fixture to the physics body along with some user data
	(m_body->CreateFixture(&l_fixtureDef))->SetUserData((void*)(int)FixtureType::Platform);


	// Setup the SFML object used to render this object/class:
	m_shape.setSize(size);
	m_shape.setOrigin(halfWidth, halfHeight);
	m_shape.setPosition(position);
	m_shape.setRotation(0);
	m_shape.setFillColor(colour);
}

void Platform::setUserData(void* userData)
{
	if (!userData)
	{
		m_body->SetUserData(new pair<string, void*>(typeid(Platform).name(), this));
	}
	else
		m_body->SetUserData(userData);
}

void Platform::update()
{
	b2Vec2 pos = m_body->GetPosition();
	m_shape.setPosition(pos.x, pos.y);

	float angle = m_body->GetAngle() * RAD2DEG;
	m_shape.setRotation(angle);
}

void Platform::draw(RenderTarget& target, RenderStates states) const
{
	target.draw(m_shape);
}
