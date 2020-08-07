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
			player->registerGroundContact(true, fixtB);
		}

		if (fixtType == FixtureType::Destructor || fixtType == FixtureType::Creator)
		{
			pair<string, void*> userData = *((pair<string, void*>*) fixtA->GetBody()->GetUserData());
			WorldGenerator* worldGen = static_cast<WorldGenerator*>(userData.second);
			worldGen->onAction(fixtA, fixtB);
		}
	}

	if (userDataB)
	{
		FixtureType fixtType = static_cast<FixtureType>((int)userDataB);

		if (fixtType == FixtureType::Sensor)
		{
			b2Body* body = fixtB->GetBody();
			pair<string, void*> userData = *((pair<string, void*>*) body->GetUserData());
			Player* player = static_cast<Player*>(userData.second);
			player->registerGroundContact(true, fixtA);
		}

		if (fixtType == FixtureType::Destructor || fixtType == FixtureType::Creator)
		{
			pair<string, void*> userData = *((pair<string, void*>*) fixtB->GetBody()->GetUserData());
			WorldGenerator* worldGen = static_cast<WorldGenerator*>(userData.second);
			worldGen->onAction(fixtB, fixtA);
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
			player->registerGroundContact(false, fixtB);
		}

		if (fixtType == FixtureType::Destructor || fixtType == FixtureType::Creator)
		{
			pair<string, void*> userData = *((pair<string, void*>*) fixtA->GetBody()->GetUserData());
			WorldGenerator* worldGen = static_cast<WorldGenerator*>(userData.second);
			worldGen->offAction(fixtA, fixtB);
		}
	}

	if (userDataB)
	{
		FixtureType fixtType = static_cast<FixtureType>((int)userDataB);

		if (fixtType == FixtureType::Sensor)
		{
			b2Body* body = fixtB->GetBody();
			pair<string, void*> userData = *((pair<string, void*>*) body->GetUserData());
			Player* player = static_cast<Player*>(userData.second);
			player->registerGroundContact(false, fixtA);
		}

		if (fixtType == FixtureType::Destructor || fixtType == FixtureType::Creator)
		{
			pair<string, void*> userData = *((pair<string, void*>*) fixtB->GetBody()->GetUserData());
			WorldGenerator* worldGen = static_cast<WorldGenerator*>(userData.second);
			worldGen->offAction(fixtB, fixtA);
		}
	}
}
