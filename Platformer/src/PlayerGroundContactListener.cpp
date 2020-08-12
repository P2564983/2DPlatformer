#include "PlayerGroundContactListener.h"

void PlayerGroundContactListener::BeginContact(b2Contact* contact)
{
	// Get the fixtures that collided:
	b2Fixture* fixtA = contact->GetFixtureA();
	b2Fixture* fixtB = contact->GetFixtureB();

	// Get the bodies that collided
	b2Body* bodyA = fixtA->GetBody();
	b2Body* bodyB = fixtB->GetBody();

	// Check if user data was set
	void* bodyAUserData = bodyA->GetUserData();
	if (bodyAUserData)
	{
		pair<string, void*> userData = *((pair<string, void*>*) bodyAUserData);
		if (typeid(PhysicalThing).name() == userData.first)
		{
			PhysicalThing* object = static_cast<PhysicalThing*>(userData.second);
			object->startCollision(fixtA, fixtB);
		}
	}

	void* bodyBUserData = bodyB->GetUserData();
	if (bodyBUserData)
	{
		pair<string, void*> userData = *((pair<string, void*>*) bodyBUserData);
		if (typeid(PhysicalThing).name() == userData.first)
		{
			PhysicalThing* object = static_cast<PhysicalThing*>(userData.second);
			object->startCollision(fixtB, fixtA);
		}
	}
}

void PlayerGroundContactListener::EndContact(b2Contact* contact)
{
	// Get the fixtures that collided:
	b2Fixture* fixtA = contact->GetFixtureA();
	b2Fixture* fixtB = contact->GetFixtureB();

	// Check if user data was set
	void* bodyUserData = fixtA->GetBody()->GetUserData();
	if (bodyUserData)
	{
		pair<string, void*> userData = *((pair<string, void*>*) bodyUserData);
		if (typeid(PhysicalThing).name() == userData.first)
		{
			PhysicalThing* object = static_cast<PhysicalThing*>(userData.second);
			object->endCollision(fixtA, fixtB);
		}
	}

	bodyUserData = fixtB->GetBody()->GetUserData();
	if (bodyUserData)
	{
		pair<string, void*> userData = *((pair<string, void*>*) bodyUserData);
		if (typeid(PhysicalThing).name() == userData.first)
		{
			PhysicalThing* object = static_cast<PhysicalThing*>(userData.second);
			object->endCollision(fixtB, fixtA);
		}
	}
}
