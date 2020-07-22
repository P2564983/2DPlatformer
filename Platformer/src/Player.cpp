#include "..\include\Player.h"

Player::Player(b2World* world, const sf::Vector2f& position, DynamicBlock dB) : m_playerBlock(dB)
{
	//m_playerBlock = new DynamicBlock(world, position, sf::Vector2f(1.0f, 1.0f), 0.0f, PhysicalThing::CollisionFilter::SIXTEEN);
}
