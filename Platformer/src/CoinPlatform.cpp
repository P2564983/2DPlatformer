#include "CoinPlatform.h"

CoinPlatform::CoinPlatform(b2World* world, Vector2f& position, Vector2f& size, const Color colour)
	: Platform(world, position, size, colour) // Call the parent class to create a platform
{
	// Set the platform user data after it is created:
	Platform::setUserData();

	// Create coins
	int coinsToCreate = max(0, (int)size.x - 2); // trunucation expected to provide padding on platform edges
	Vector2f coinStart = position - Vector2f((coinsToCreate - 1)/2.0f, size.y * 0.5f + 0.3f); // The starting position of the first coin

	for (int i = 0; i < coinsToCreate; i++)
	{
		Coin* coin = new Coin(world, coinStart + Vector2f(i, 0));
		m_coins.insert(coin);
		coin->setUserData();
	}
}

CoinPlatform::~CoinPlatform()
{
	for (auto coin : m_coins) 
		delete coin;
	m_coins.clear();
}

void CoinPlatform::update()
{
	Platform::update(); // Call the parent class update method to update platform

	// Check if any coins have been collected, if so add them to removal list:
	set<Coin*> coinsToRemove;
	for (auto coin : m_coins)
	{
		if (coin->isCollected())
			coinsToRemove.insert(coin);
	}

	for (auto coinToRemove : coinsToRemove)
	{
		m_coins.erase(coinToRemove);
		delete coinToRemove;
	}
	coinsToRemove.clear();
}

void CoinPlatform::draw(RenderTarget& target, RenderStates states) const
{
	Platform::draw(target, states);	// Call the parent class draw method to draw the platform
	for (auto coin : m_coins) target.draw(*coin);
}
