#include "..\include\Player.h"

Player::Player(b2World* world, const sf::Vector2f& position)
	: DynamicBlock(world, position, sf::Vector2f(1.f, 1.f), 0, PhysicalThing::CollisionFilter::ONE)
{
	setFillColor(Color::Black);
}