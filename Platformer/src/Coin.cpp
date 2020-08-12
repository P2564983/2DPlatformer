#include "..\include\Coin.h"

Coin::Coin(b2World* world, const sf::Vector2f& position)
{
	// Body in the Physics world
	b2BodyDef l_bodyDef;
	l_bodyDef.position.Set(position.x, position.y);
	l_bodyDef.angle = 0;
	l_bodyDef.type = b2_staticBody;
	m_body = world->CreateBody(&l_bodyDef);

	// Box2D Shape
	b2CircleShape l_shape;
	l_shape.m_radius = m_radius;

	// Box2D Fixture
	b2FixtureDef l_fixtureDef;
	l_fixtureDef.shape = &l_shape;
	l_fixtureDef.isSensor = true; // Make it a sensor to become aware of collision
	// Setup collision filtering - A coin can only collide with a player:
	l_fixtureDef.filter.categoryBits = (uint16)CollisionFilter::Collectible;
	l_fixtureDef.filter.maskBits = (uint16)CollisionFilter::Player;
	m_body->CreateFixture(&l_fixtureDef);

	m_shape.setRadius(m_radius);
	m_shape.setOrigin(m_radius, m_radius);
	m_shape.setPosition(position);
	m_shape.setRotation(0);
	m_shape.setFillColor(Color(255, 223, 0)); // Goldish colour

	setUserData();
}

void Coin::update()
{
	// The coins body may be deleted before it is properly removed from the world:
	if (!m_body) return;

	// Destroy the physics body if the coin has been collected:
	if (m_collected)
	{
		m_body->GetWorld()->DestroyBody(m_body);
		m_body = nullptr;
	}
}

void Coin::draw(RenderTarget& target, RenderStates states) const
{
	// Coin does not have a body, it has been collected/destroyed:
	if (!m_body) return;

	// Draw the coin shape
	target.draw(m_shape);

	// Draw a smaller circle within
	float smallRadius = m_radius * 0.6f;

	CircleShape smallCircle(smallRadius);
	smallCircle.setOrigin(smallRadius, smallRadius);
	smallCircle.setPosition(m_shape.getPosition());
	smallCircle.setFillColor(Color::Red);
	target.draw(smallCircle);
}

void Coin::startCollision(b2Fixture* thisFixture, b2Fixture* collidedWith)
{
	// Collision filter ensures only a player collides with coin
	m_collected = true;
	Score::addToScore(1);
}
