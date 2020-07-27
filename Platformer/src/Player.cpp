#include "..\include\Player.h"

Player::Player(b2World* world, const sf::Vector2f& position)
	//: DynamicBlock(world, position, sf::Vector2f(0.5f, 0.5f), 0, PhysicalThing::CollisionFilter::ONE)
{
	//set up a dynamic body
	b2BodyDef bodyDef;
	bodyDef.type = b2_dynamicBody;
	bodyDef.position.Set(position.x, position.y);
	m_body = world->CreateBody(&bodyDef);

	//prepare a shape definition
	b2CircleShape circleShape;
	circleShape.m_radius = 0.5f;
	b2FixtureDef fixtureDef;
	fixtureDef.shape = &circleShape;
	fixtureDef.density = 1;		// density * area = mass
	fixtureDef.friction = 0.4f;	// 0 = completely frictionless ; 1 = max friction
	fixtureDef.restitution = 1.0f;	// 0 = No Bounce; 1 = completely bouncy
	m_body->CreateFixture(&fixtureDef);	//add a fixture to the body

	// SFML shape
	m_shape.setPosition(position);
	m_shape.setRadius(0.5f);
	m_shape.setOrigin(0.5f, 0.5f);
	m_shape.setRotation(0);
	m_shape.setFillColor(Color::Black);

	// Other properties
	m_speed = 3.f;
}

void Player::move(const b2Vec2& direction) 
{
	cout << "Moving: " << direction.x << ", " << direction.y << endl;
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

const Vector2f Player::getPosition() const
{
	b2Vec2 pos = m_body->GetPosition();
	return Vector2f(pos.x, pos.y);
}

void Player::update()
{
	b2Vec2 pos = m_body->GetPosition();
	m_shape.setPosition(pos.x, pos.y);

	float angle = m_body->GetAngle() * RAD2DEG;
	m_shape.setRotation(angle);
}

void Player::draw(RenderTarget& target, RenderStates states) const
{
	target.draw(m_shape); // Draw the Circle Shape

	// Add a line
	RectangleShape line(Vector2f(m_shape.getRadius(), 0.01f));
	line.setPosition(m_shape.getPosition());
	line.setOrigin(0.f, 0.005f);
	line.rotate(m_shape.getRotation());
	target.draw(line);
}
