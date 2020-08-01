#include "CoinPlayerContactListener.h"

void CoinPlayerContactListener::BeginContact(b2Contact* contact)
{
	// Get the bodies that collided:
	b2Body* bodyA = contact->GetFixtureA()->GetBody();
	b2Body* bodyB = contact->GetFixtureB()->GetBody();

	// Get the User Data for the bodies involved in collision:
	void* uDA = bodyA->GetUserData();
	void* uDB = bodyB->GetUserData();
	if (!uDA || !uDB) return;

	// Attempt to cast user data so we can see what type of objects collided
	pair<string, void*> userDataA = *((pair<string, void*>*) uDA);
	pair<string, void*> userDataB = *((pair<string, void*>*) uDB);
	// Note userDataX.first = string (name of type); userDataX.second = void* (pointer to object).

	// For now we just want to know if anything is touching the coin (regardless of what it is)
	string coinName = typeid(Coin).name();
	Coin* coin = nullptr;
	// Something has touched a coin
	if (coinName == userDataA.first)	coin = static_cast<Coin*>(userDataA.second);
	if (coinName == userDataB.first)	coin = static_cast<Coin*>(userDataB.second);

	if (coin != nullptr)
	{
		coin->onContact();
	}
	//if (coin != nullptr)	cout << "BeginContact:\tCoin was involved in collision" << endl;
	return;



	// ToDo: Finish this code
	// Check if bodyA is the player:
	if (typeid(Player).name() == userDataA.first)
	{
		// Check if player has collided with coin:
		if (typeid(Coin).name() == userDataB.first)
		{
			Coin* coin = static_cast<Coin*>(userDataB.second);
		}
	}

	// Check if bodyB is the player:
	if (typeid(Player).name() == userDataB.first)
	{
		// Check if player has collided with coin:
		if (typeid(Coin).name() == userDataA.first)
		{

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

	// For now we just want to know if a coin was involved in collision
	string coinName = typeid(Coin).name();
	Coin* coin = nullptr;
	// Something had touched a coin
	if (coinName == userDataA.first)	coin = static_cast<Coin*>(userDataA.second);
	if (coinName == userDataB.first)	coin = static_cast<Coin*>(userDataB.second);

	if (coin != nullptr)	coin->onSeperation();
	//if (coin != nullptr)	cout << "EndContact:\tCoin was involved in collision" << endl;
	return;
}
