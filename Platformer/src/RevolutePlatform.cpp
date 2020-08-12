#include "RevolutePlatform.h"

RevolutePlatform::RevolutePlatform(b2World* world, Vector2f& position, Vector2f& size, const Color colour)
	: Platform(world, position, size, colour) // Call the parent class to create a platform
{
	// Create a revolute joint at the centre of platform
	b2FixtureDef l_fixtureDef;
	b2BodyDef l_bodyDef; // body for anchor

	// Create bodyA:
	// Use platform as body
	m_body->SetFixedRotation(false);
	m_body->SetType(b2_dynamicBody);

	// Create bodyB (the anchor)
	l_bodyDef.type = b2_staticBody; // the hinge does not move
	l_bodyDef.position.Set(position.x, position.y); // hinge placed at platform centre
	l_bodyDef.angle = 0;
	m_anchor = world->CreateBody(&l_bodyDef);
	// Anchor Shape and Fixture:
	float radius = fminf(size.x * 0.5f, size.y * 0.5f);
	b2CircleShape l_circ;
	//l_circ.m_radius = radius;
	l_fixtureDef.shape = &l_circ;
	l_fixtureDef.density = l_fixtureDef.friction = l_fixtureDef.restitution = 0;
	l_fixtureDef.filter.maskBits = (int)CollisionFilter::Nothing; // Anchor collided with nothing
	l_fixtureDef.userData = (void*)(int)FixtureType::Hinge;
	m_anchor->CreateFixture(&l_fixtureDef);

	// Create the revolute joint
	b2RevoluteJointDef revoluteJointDef;
	revoluteJointDef.bodyA = m_body;	// bodyA = platform
	revoluteJointDef.bodyB = m_anchor;	// bodyB = anchor
	revoluteJointDef.collideConnected = false;	// platform and anchor do not collide (they can overlap)
	revoluteJointDef.localAnchorA.Set(0.f, 0.f);	// Centre of platform
	revoluteJointDef.localAnchorB.Set(0.f, 0.f);	// Centre of anchor (circle)
	// Apply limits to joint to prevent over-rotation:
	revoluteJointDef.enableLimit = true;
	revoluteJointDef.lowerAngle = -30 * DEG2RAD;
	revoluteJointDef.upperAngle = +30 * DEG2RAD;
	// Enable motor
	//revoluteJointDef.enableMotor = true;
	//revoluteJointDef.maxMotorTorque = 180;
	//revoluteJointDef.motorSpeed = -90 * DEG2RAD; // rotate xdeg per/second
	// Create the joint
	m_joint = (b2RevoluteJoint*)world->CreateJoint(&revoluteJointDef);
}

RevolutePlatform::~RevolutePlatform()
{
	if (m_anchor)
	{
		m_anchor->GetWorld()->DestroyBody(m_anchor);
		m_anchor = nullptr;
		m_joint = nullptr; // Destroying the body will automatically destory the joint, Box2D handles delete
	}
}
