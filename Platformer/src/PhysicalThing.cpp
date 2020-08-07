#include "PhysicalThing.h"

void PhysicalThing::setUserData(void* data)
{
	m_body->SetUserData(data);
}

b2Vec2 PhysicalThing::getPositionB2()
{
	return m_body->GetPosition();
}

b2Body* PhysicalThing::getBody()
{
	return m_body;
}
