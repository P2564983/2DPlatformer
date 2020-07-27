#include "..\include\Player.h"

Player::Player(b2World* world, const sf::Vector2f& position)
	: DynamicBlock(world, position, sf::Vector2f(0.5f, 0.5f), 0, PhysicalThing::CollisionFilter::ONE)
{
	setFillColor(Color::Black);
	m_speed = 3.f;
}

void Player::move(const b2Vec2& direction) 
{
	b2Vec2 impulse = m_body->GetMass() * ((m_speed * direction) - m_body->GetLinearVelocity());
	m_body->ApplyLinearImpulseToCenter(impulse, true);
	return;
}

void Player::increaseSpeed(const float amount)
{
	m_speed = b2Clamp(m_speed + amount, 0.1f, 5.f);	// Clamp speed between 0.1 and 5
	std::cout << "Player Speed = " << m_speed << endl;
	b2Vec2 b2 = m_body->GetPosition();
}

