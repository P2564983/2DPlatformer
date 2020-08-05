#include "CoinPlayerContactListener.h"

void CoinPlayerContactListener::BeginContact(b2Contact* contact)
{
	// Get the bodies that collided:
	b2Body* bodyA = contact->GetFixtureA()->GetBody();
	b2Body* bodyB = contact->GetFixtureB()->GetBody();

	// Get the User Data for the bodies involved in collision:
	void* uDA = bodyA->GetUserData();
	void* uDB = bodyB->GetUserData();
	if (!uDA || !uDB) return; // No user data was set, we cannot do anything.

	// Attempt to cast user data so we can see what type of objects collided
	pair<string, void*> userDataA = *((pair<string, void*>*) uDA);
	pair<string, void*> userDataB = *((pair<string, void*>*) uDB);
	// Note userDataX.first = string (name of type); userDataX.second = void* (pointer to object).

	// Determine what is what so onContact() is called on the coin object
	string coinName = typeid(Coin).name();
	string playerName = typeid(Player).name();

	// Check if bodyA is the player:
	if (userDataA.first == playerName)
	{
		// Check if player has collided with coin:
		if (userDataB.first == coinName)
		{
			Coin* coin = static_cast<Coin*>(userDataB.second);
			if (coin) coin->onContact();
		}
	}

	// Otherwise check if bodyB is the player:
	if (userDataB.first == playerName)
	{
		// Check if player has collided with coin:
		if (userDataA.first == coinName)
		{
			Coin* coin = static_cast<Coin*>(userDataA.second);
			if (coin) coin->onContact();
		}
	}
}

void CoinPlayerContactListener::EndContact(b2Contact* contact)
{
	// Get the bodies that ended collision:
	b2Body* bodyA = contact->GetFixtureA()->GetBody();
	b2Body* bodyB = contact->GetFixtureB()->GetBody();

	// Get the User Data for the bodies involved in collision:
	void* uDA = bodyA->GetUserData();
	void* uDB = bodyB->GetUserData();
	if (!uDA || !uDB) return;

	//// Attempt to cast user data so we can see what type of objects collided
	pair<string, void*> userDataA = *((pair<string, void*>*) uDA);
	pair<string, void*> userDataB = *((pair<string, void*>*) uDB);
	// Note userDataX.first = string (name of type); userDataX.second = void* (pointer to object).

	// Determine what is what so onSeperation() is called on the coin object
	string coinName = typeid(Coin).name();
	string playerName = typeid(Player).name();

	// Check if bodyA is the player:
	if (userDataA.first == playerName)
	{
		// Check if player has collided with coin:
		if (userDataB.first == coinName)
		{
			Coin* coin = static_cast<Coin*>(userDataB.second);
			if (coin) coin->onContact();
		}
	}

	// Otherwise check if bodyB is the player:
	if (userDataB.first == playerName)
	{
		// Check if player has collided with coin:
		if (userDataA.first == coinName)
		{
			Coin* coin = static_cast<Coin*>(userDataA.second);
			if (coin) coin->onContact();
		}
	}
}
