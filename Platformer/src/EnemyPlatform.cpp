#include "EnemyPlatform.h"

EnemyPlatform::EnemyPlatform(b2World* world, Vector2f& position, Vector2f& size, const Color colour)
	: Platform(world, position, size, colour) // Call the parent class to create a platform
{
	// Set the platform user data after it is created:
	Platform::setUserData();

	// Create the enemy on the platform:
	m_enemy = new Enemy(world, this);
	m_enemy->setUserData();
}

EnemyPlatform::~EnemyPlatform()
{
	// Base Platform class handles platform cleanup
	if(m_enemy) delete m_enemy;
}

void EnemyPlatform::update()
{
	Platform::update(); // Call the parent class update method

	if (!m_enemy) return; // Enemy has been killed
	if (m_enemy->isDead())
	{
		delete m_enemy;
		m_enemy = nullptr;
	}
	else
		m_enemy->update();
}

void EnemyPlatform::draw(RenderTarget& target, RenderStates states) const
{
	Platform::draw(target, states);	// Call the parent class draw method to draw the platform
	if(m_enemy) target.draw(*m_enemy); // The enemy could potentially have been killed
}
