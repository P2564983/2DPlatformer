#include "..\include\Player.h"

Player::Player(b2World* world, const sf::Vector2f& position)
	//: DynamicBlock(world, position, sf::Vector2f(0.5f, 0.5f), 0, PhysicalThing::CollisionFilter::ONE)
{
	//set up a dynamic body
	b2BodyDef bodyDef;
	bodyDef.type = b2_dynamicBody;
	bodyDef.position.Set(position.x, position.y);
	m_body = world->CreateBody(&bodyDef);
	m_body->SetGravityScale(0);	// REMOVE: cancels gravity (use -1 to reverse gravity, etc)

	//prepare a shape definition
	b2CircleShape circleShape;
	circleShape.m_radius = 0.5f;
	b2FixtureDef fixtureDef;
	fixtureDef.shape = &circleShape;
	fixtureDef.density = m_density;		
	fixtureDef.friction = m_friction;	
	fixtureDef.restitution = m_restitution;	
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
	// Move in all directions
	/*cout << "Moving: " << direction.x << ", " << direction.y << endl;
	b2Vec2 impulse = m_body->GetMass() * ((m_speed * direction) - m_body->GetLinearVelocity());
	m_body->ApplyLinearImpulseToCenter(impulse, true);*/

	// Move only on x-axis
	b2Vec2 vel = m_body->GetLinearVelocity();
	float desiredVel = direction.x * m_speed;
	float velChange = desiredVel - m_body->GetLinearVelocity().x;
	float impulse = m_body->GetMass() * velChange;
	m_body->ApplyLinearImpulse(b2Vec2(impulse, 0), m_body->GetWorldCenter(), true);
}

void Player::rotateTowards(b2Vec2 target)
{
	b2Vec2 toTarget = target - m_body->GetPosition();
	float desiredAngle = atan2f(toTarget.y, toTarget.x);
	//m_body->SetTransform(m_body->GetPosition(), desiredAngle);

	float currentAngle = m_body->GetAngle();
	float totalRotation = desiredAngle - currentAngle;
	if (totalRotation < (-180 * DEG2RAD))
	{
		cout << "Total Rotation (" << totalRotation * RAD2DEG << ") is < -180 degrees. " << endl;
		while (totalRotation < -180 * DEGTORAD) totalRotation += (360 * DEGTORAD);
	}
	if (totalRotation > (180 * DEG2RAD))
	{
		cout << "Total Rotation (" << totalRotation * RAD2DEG << ") is > 180 degrees. " << endl;
		while (totalRotation > 180 * DEGTORAD) totalRotation -= (360 * DEGTORAD);
	}

	cout << "Current Angle = \t" << currentAngle << " radians \t " << currentAngle * RAD2DEG << " degrees" << endl;
	cout << "Desired Angle = \t" << desiredAngle << " radians \t " << desiredAngle * RAD2DEG << " degrees" << endl;
	cout << "Amount To Rotate = \t" << totalRotation << " radians \t " << totalRotation * RAD2DEG << " degrees\n" << endl;
}

bool Player::rotateTowards(b2Vec2 target, float changeRadians)
{
	float currentAngle = m_body->GetAngle();

	b2Vec2 toTarget = target - m_body->GetPosition();
	float desiredAngle = atan2f(toTarget.y, toTarget.x);	// in radians

	float totalRotation = desiredAngle - currentAngle;

	if (totalRotation == 0) return true;
	while (totalRotation < -180 * DEGTORAD) totalRotation += (360 * DEGTORAD);
	while (totalRotation > 180 * DEGTORAD) totalRotation -= (360 * DEGTORAD);

	float newAngle = currentAngle + b2Min(changeRadians, b2Max(-changeRadians, totalRotation));

	m_body->SetTransform(m_body->GetPosition(), newAngle);

	return false;
}

void Player::increaseSpeed(const float amount)
{
	m_speed = b2Clamp(m_speed + amount, 0.1f, 10.f);	// Clamp speed between param2 and param3
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

b2Body* Player::getBody() const
{
	return m_body;
}
