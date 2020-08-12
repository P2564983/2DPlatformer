#include "PhysicalThing.h"

PhysicalThing::~PhysicalThing()
{
	if (m_body)
	{
		m_body->GetWorld()->DestroyBody(m_body);
		m_body = nullptr;
	}
}

void PhysicalThing::setUserData(void* data)
{
	// No body to attach user data to
	if (!m_body) return;

	m_body->SetUserData(data ? data : new pair<string, void*>(typeid(PhysicalThing).name(), this));
}

b2Vec2 PhysicalThing::getPositionB2() const
{
	if (!m_body) return b2Vec2(0, 0);
	return m_body->GetPosition();
}

Vector2f PhysicalThing::getPositionV2F() const
{
	if (!m_body) return Vector2f(0, 0);
	b2Vec2 pos = m_body->GetPosition();
	return Vector2f(pos.x, pos.y);
}
