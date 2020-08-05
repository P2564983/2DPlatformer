#include "PlayerGroundContactListener.h"

void PlayerGroundContactListener::BeginContact(b2Contact* contact)
{
	// Get the fixtures that collided:
	b2Fixture* fixtA = contact->GetFixtureA();
	b2Fixture* fixtB = contact->GetFixtureB();

	void* userDataA = fixtA->GetUserData();
	void* userDataB = fixtB->GetUserData();
	if (!userDataA && !userDataB) return; // neither have any user data

	if (userDataA)
	{
		FixtureType fixtType = static_cast<FixtureType>((int)userDataA);

		if (fixtType == FixtureType::Sensor)
		{
			b2Body* body = fixtA->GetBody();
			pair<string, void*> userData = *((pair<string, void*>*) body->GetUserData());
			Player* player = static_cast<Player*>(userData.second);
			player->registerGroundContact(1);
		}
	}

	if (userDataB)
	{
		FixtureType fixtType = static_cast<FixtureType>((int)userDataA);

		if (fixtType == FixtureType::Sensor)
		{
			b2Body* body = fixtA->GetBody();
			pair<string, void*> userData = *((pair<string, void*>*) body->GetUserData());
			Player* player = static_cast<Player*>(userData.second);
			player->registerGroundContact(1);
		}
	}
}

void PlayerGroundContactListener::EndContact(b2Contact* contact)
{
	// Get the fixtures that collided:
	b2Fixture* fixtA = contact->GetFixtureA();
	b2Fixture* fixtB = contact->GetFixtureB();

	void* userDataA = fixtA->GetUserData();
	void* userDataB = fixtB->GetUserData();
	if (!userDataA && !userDataB) return; // neither have any user data

	if (userDataA)
	{
		FixtureType fixtType = static_cast<FixtureType>((int)userDataA);

		if (fixtType == FixtureType::Sensor)
		{
			b2Body* body = fixtA->GetBody();
			pair<string, void*> userData = *((pair<string, void*>*) body->GetUserData());
			Player* player = static_cast<Player*>(userData.second);
			player->registerGroundContact(-1);
		}
	}

	if (userDataB)
	{
		FixtureType fixtType = static_cast<FixtureType>((int)userDataA);

		if (fixtType == FixtureType::Sensor)
		{
			b2Body* body = fixtA->GetBody();
			pair<string, void*> userData = *((pair<string, void*>*) body->GetUserData());
			Player* player = static_cast<Player*>(userData.second);
			player->registerGroundContact(-1);
		}
	}
}
