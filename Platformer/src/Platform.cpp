#include "Platform.h"

Platform::Platform(b2World* world, Vector2f& position, Vector2f& size, const Color colour)
{
	m_size = size;
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

	// Create a fixture definition for the platform shape:
	b2FixtureDef l_fixtureDef;
	l_fixtureDef.shape = &l_shape;
	l_fixtureDef.density = mk_fDensity;
	l_fixtureDef.friction = mk_fFriction;
	l_fixtureDef.restitution = 0; // not bouncy
	// Setup collision filtering:
	l_fixtureDef.filter.categoryBits = (uint16)CollisionFilter::Platform;
	// Attach the fixture to the physics body along with some user data
	(m_body->CreateFixture(&l_fixtureDef))->SetUserData((void*)(int)FixtureType::Platform);

	// Common sensor properties:
	b2Vec2 sensorSize = b2Vec2(0.1f, m_size.y);
	l_fixtureDef.isSensor = true;
	l_fixtureDef.density = l_fixtureDef.friction = l_fixtureDef.restitution = 0;

	// Create a platform start sensor used for collision detection
	b2Vec2 sensorPosition = b2Vec2(-halfWidth, -halfHeight);
	l_shape.SetAsBox(sensorSize.x, sensorSize.y, sensorPosition, 0);
	platformStartSensor = m_body->CreateFixture(&l_fixtureDef);
	platformStartSensor->SetUserData((void*)(int)SensorType::PlatformStart);

	// Create a platform end sensor used for collision detection
	sensorPosition.x = halfWidth;
	l_shape.SetAsBox(sensorSize.x, sensorSize.y, sensorPosition, 0);
	platformEndSensor = m_body->CreateFixture(&l_fixtureDef);
	platformEndSensor->SetUserData((void*)(int)SensorType::PlatformEnd);

	// Setup the SFML object used to render this object/class:
	m_shape.setSize(size);
	m_shape.setOrigin(halfWidth, halfHeight);
	m_shape.setPosition(position);
	m_shape.setRotation(0);
	m_shape.setFillColor(colour);

	setUserData();
}

Platform::~Platform()
{
	platformStartSensor = platformEndSensor = nullptr;
}

void Platform::update()
{
	if (!m_body) return;

	b2Vec2 pos = m_body->GetPosition();
	m_shape.setPosition(pos.x, pos.y);

	float angle = m_body->GetAngle() * RAD2DEG;
	m_shape.setRotation(angle);
}

void Platform::draw(RenderTarget& target, RenderStates states) const
{
	if (m_body)	target.draw(m_shape);
}