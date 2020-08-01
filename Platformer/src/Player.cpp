#include "..\include\Player.h"

Player::Player(b2World* world, const sf::Vector2f& position)
	//: DynamicBlock(world, position, sf::Vector2f(0.5f, 0.5f), 0, PhysicalThing::CollisionFilter::ONE)
{
	//set up a dynamic body
	b2BodyDef bodyDef;
	bodyDef.type = b2_dynamicBody;
	bodyDef.position.Set(position.x, position.y);
	m_body = world->CreateBody(&bodyDef);
	//m_body->SetGravityScale(0);	// REMOVE: cancels gravity (use -1 to reverse gravity, etc)
	m_body->SetFixedRotation(true);

	//prepare a shape definition
	b2PolygonShape shape;
	shape.SetAsBox(0.25f, 0.25f);
	shape.m_radius = 0;
	b2FixtureDef fixtureDef;
	fixtureDef.shape = &shape;
	fixtureDef.density = m_density;		
	fixtureDef.friction = m_friction;	
	fixtureDef.restitution = m_restitution;	
	m_body->CreateFixture(&fixtureDef);	//add a fixture to the body

	// SFML shape
	m_shape.setPosition(position);
	m_shape.setSize(Vector2f(0.5f, 0.5f));
	m_shape.setOrigin(0.25f, 0.25f);
	m_shape.setRotation(0);
	m_shape.setFillColor(Color::Black);
	m_shape.setOutlineThickness(0.f);

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

void Player::jump()
{
	//// Setting velocity directly
	//b2Vec2 vel = m_body->GetLinearVelocity();
	//vel.y = -10;	// upwards - don't change x velocity (- is up; + is down)
	//m_body->SetLinearVelocity(vel);

	//// Using A Force
	//m_body->ApplyForceToCenter(b2Vec2(0, -100), true);
	//// ToDo: Add 'int remainingJumpSteps = 0;' to game.h and then keep calling jump() in game::update()

	// Using An Impulse
	float impulse = m_body->GetMass() * -m_speed;
	m_body->ApplyLinearImpulseToCenter(b2Vec2(0, impulse), true);

}

void Player::rotateTowards(b2Vec2 target)
{
	m_body->ApplyAngularImpulse(1.0f, true);
	return;

	float currentAngle = m_body->GetAngle();

	b2Vec2 toTarget = target - m_body->GetPosition();
	float desiredAngle = atan2f(toTarget.y, toTarget.x);

	float nextAngle = currentAngle + m_body->GetAngularVelocity() / 60.0; // peak ahead

	float totalRotation = desiredAngle - nextAngle;
	while (totalRotation < -180 * DEGTORAD) totalRotation += 360 * DEGTORAD;
	while (totalRotation > 180 * DEGTORAD) totalRotation -= 360 * DEGTORAD;

	float desiredAngularVelocity = totalRotation * 60;
	float impulse = m_body->GetInertia() * desiredAngularVelocity;
	m_body->ApplyAngularImpulse(impulse, true);
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

	//// Setting Angle Directly
	//float newAngle = currentAngle + b2Min(changeRadians, b2Max(-changeRadians, totalRotation));
	//m_body->SetTransform(m_body->GetPosition(), newAngle);

	// Using Torque
	float nextAngle = currentAngle + m_body->GetAngularVelocity() / 3.0;
	totalRotation = desiredAngle - nextAngle;
	m_body->ApplyTorque(totalRotation < 0 ? -1 : 1, true);

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
	RectangleShape line(Vector2f(0.25f, 0.01f));
	line.setPosition(m_shape.getPosition());
	line.setOrigin(0.f, 0.005f);
	line.rotate(m_shape.getRotation());
	target.draw(line);
}

b2Body* Player::getBody() const
{
	return m_body;
}
