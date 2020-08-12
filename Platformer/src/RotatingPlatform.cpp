#include "RotatingPlatform.h"

RotatingPlatform::RotatingPlatform(b2World* world, Vector2f position, Color colour)
{
	float halfWidth = width * 0.5f;
	float halfHeight = height * 0.5f;
	float radius = fminf(halfWidth, halfHeight);

	b2BodyDef l_bodyDef;
	b2FixtureDef l_fixtureDef;

	// First create the platform body:
	l_bodyDef.type = b2_dynamicBody;
	l_bodyDef.position.Set(position.x, position.y);
	l_bodyDef.angle = 0;
	m_body = world->CreateBody(&l_bodyDef);
	// Platform Shape and Fixture:
	b2PolygonShape l_shape;
	l_shape.SetAsBox(halfWidth, halfHeight);
	l_shape.m_radius = 0.0f;
	l_fixtureDef.shape = &l_shape;
	l_fixtureDef.density = mk_fDensity;
	l_fixtureDef.friction = mk_fFriction;
	l_fixtureDef.restitution = mk_fRestitution;
	l_fixtureDef.restitution = 0;
	m_body->CreateFixture(&l_fixtureDef)->SetUserData((void*)(int)FixtureType::RotatingPlatform);;
	m_body->SetAngularDamping(0.1f);

	// Now create the anchor body:
	l_bodyDef.type = b2_staticBody;	// prevents platform from moving, can only rotate
	m_anchor = world->CreateBody(&l_bodyDef);
	// Anchor Shape and Fixture:
	b2CircleShape l_circ;
	l_circ.m_radius = radius;
	l_fixtureDef.shape = &l_circ;
	m_anchor->CreateFixture(&l_fixtureDef)->SetUserData((void*)(int)FixtureType::Platform);

	// Now create the revolute joint:
	b2RevoluteJointDef revoluteJointDef;
	revoluteJointDef.bodyA = m_body;	// bodyA = platform
	revoluteJointDef.bodyB = m_anchor;	// bodyB == anchor
	revoluteJointDef.collideConnected = false;	// platform and anchor do not collide (they can overlap)
	revoluteJointDef.localAnchorA.Set(0.f, 0.f);	// Centre of platform
	revoluteJointDef.localAnchorB.Set(0.f, 0.f);	// Centre of anchor (circle)
	// Apply limits to joint to prevent over-rotation:
	//revoluteJointDef.enableLimit = true;
	//revoluteJointDef.lowerAngle = -60 * DEG2RAD;
	//revoluteJointDef.upperAngle = +60 * DEG2RAD;
	// Enable motor
	revoluteJointDef.enableMotor = true;
	revoluteJointDef.maxMotorTorque = 180;
	revoluteJointDef.motorSpeed = -90 * DEG2RAD; // rotate xdeg per/second
	// Create the joint
	m_joint = (b2RevoluteJoint*)world->CreateJoint(&revoluteJointDef);

	// Set SFML shape properties for rendering:
	// Starting with the platform (m_rectangle):
	m_rectangle.setSize(Vector2f(width, height));
	m_rectangle.setOrigin(halfWidth, halfHeight);
	m_rectangle.setPosition(position);
	m_rectangle.setRotation(0);
	m_rectangle.setFillColor(colour);
	m_rectangle.setOutlineThickness(0.f);
	// And now the anchor:
	m_circle.setRadius(radius);
	m_circle.setOrigin(radius, radius);
	m_circle.setPosition(position);	// at centre of platform
	m_circle.setRotation(0);
	m_circle.setFillColor(Color::Red);
}

void RotatingPlatform::setUserData(void* userData)
{
	if (!userData)
	{
		m_body->SetUserData(new pair<string, void*>(typeid(RotatingPlatform).name(), this));
	}
	else
		m_body->SetUserData(userData);
}

void RotatingPlatform::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(m_rectangle);
	target.draw(m_circle);
}

void RotatingPlatform::update()
{
	// Update platforms position and roation
	b2Vec2 pos = m_body->GetPosition();
	float angle = m_body->GetAngle() * RAD2DEG;
	m_rectangle.setPosition(pos.x, pos.y);
	m_rectangle.setRotation(angle);

	// Update anchors position and rotation (shouldn't really change as is static)
	pos = m_anchor->GetPosition();
	angle = m_anchor->GetAngle() * RAD2DEG;
	m_circle.setPosition(pos.x, pos.y);
	m_circle.setRotation(angle);
}
