#include "PhysicalThing.h"

void PhysicalThing::setUserData(void* data)
{
	m_body->SetUserData(data);
}
