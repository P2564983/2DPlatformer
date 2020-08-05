#include "..\include\Player.h"

Player::Player(b2World* world, const sf::Vector2f& position, Color colour)
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
	//shape.SetAsBox(0.25f, 0.25f);
	shape.SetAsBox(playerHalfSize.x, playerHalfSize.y);
	shape.m_radius = 0;

	// Main fixture attached to body represting player
	b2FixtureDef fixtureDef;
	fixtureDef.shape = &shape;
	fixtureDef.density = m_density;		
	fixtureDef.friction = m_friction;	
	fixtureDef.restitution = m_restitution;	
	m_body->CreateFixture(&fixtureDef);	//add a fixture to the body

	// Smaller fixture attached to body base used to determine jump
	shape.SetAsBox(sensorHalfSize.x, sensorHalfSize.y, b2Vec2(0, playerHalfSize.y), 0);
	fixtureDef.isSensor = true;
	fixtureDef.density = 0;
	groundSensorFixture = m_body->CreateFixture(&fixtureDef);
	groundSensorFixture->SetUserData((void *) (int)FixtureType::Sensor);

	// SFML shape
	m_shape.setSize(Vector2f(playerHalfSize.x * 2, playerHalfSize.y * 2));
	m_shape.setOrigin(playerHalfSize.x, playerHalfSize.y); // origin is now centre of shape (instead of top left)
	m_shape.setPosition(position);	// position set after origin changed
	m_shape.setRotation(0);
	m_shape.setFillColor(colour);
	m_shape.setOutlineThickness(0.f);

	// Other properties
	m_speed = 3.0f;
	jump(); // get the clock running
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
	static Clock clock;

	// Determine if jump is possible
	if (numOfGroundContacts <= 0) return; // player must be grounded

	// Prevent jumps for x milliseconds
	if (clock.getElapsedTime().asMilliseconds() < 1000) return;
	clock.restart();

	//// Setting velocity directly
	//b2Vec2 vel = m_body->GetLinearVelocity();
	//vel.y = -10;	// upwards - don't change x velocity (- is up; + is down)
	//m_body->SetLinearVelocity(vel);

	//// Using A Force
	//m_body->ApplyForceToCenter(b2Vec2(0, -100), true);
	//// ToDo: Add 'int remainingJumpSteps = 0;' to game.h and then keep calling jump() in game::update()

	// Using An Impulse
	float impulse = m_body->GetMass() * -(m_speed);
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

void Player::registerGroundContact(const int change)
{
	if (change > 0)
		numOfGroundContacts++;
	else if (change < 0)
		numOfGroundContacts--;
}

void Player::update()
{
	b2Vec2 pos = m_body->GetPosition();
	m_shape.setPosition(pos.x, pos.y);

	float angle = m_body->GetAngle() * RAD2DEG;
	m_shape.setRotation(angle);

	static bool runOnce = true;
	static Color initialColour;
	if (runOnce)
	{
		initialColour = m_shape.getFillColor();
		runOnce = false;
	}

	if (numOfGroundContacts > 0)
		m_shape.setFillColor(Color::Red);
	else
		m_shape.setFillColor(initialColour);
}

void Player::draw(RenderTarget& target, RenderStates states) const
{
	target.draw(m_shape); // Draw the Circle Shape

	// Draw sensor fixture
	return;
	RectangleShape sensorShape;
	sensorShape.setSize(Vector2f(sensorHalfSize.x * 2, sensorHalfSize.y * 2));
	sensorShape.setOrigin(sensorHalfSize.x, sensorHalfSize.y); // origin at centre
	sensorShape.setFillColor(Color::Yellow);
	sensorShape.setRotation(0);
	Vector2f playerPosition = m_shape.getPosition();
	sensorShape.setPosition(playerPosition.x, playerPosition.y + playerHalfSize.y);
	target.draw(sensorShape);
	return;


	// Add a line
	RectangleShape line(Vector2f(0.25f, 0.01f));
	line.setPosition(m_shape.getPosition());
	line.setOrigin(0.f, 0.005f);
	line.rotate(m_shape.getRotation());
	target.draw(line);
}

void Player::setUserData()
{
	m_body->SetUserData(new pair<string, void*>(typeid(Player).name(), this));
}

b2Body* Player::getBody() const
{
	return m_body;
}
