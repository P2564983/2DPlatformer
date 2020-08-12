#include "..\include\Player.h"

Player::Player(b2World* world, const sf::Vector2f& position, Color airColour, Color groundColour) 
	: m_airColour(airColour), m_groundColour(groundColour)
{
	//set up a dynamic body
	b2BodyDef l_bodyDef;
	l_bodyDef.type = b2_dynamicBody;
	l_bodyDef.position.Set(position.x, position.y);
	l_bodyDef.fixedRotation = false; // allow rotation
	m_body = world->CreateBody(&l_bodyDef);

	//prepare a shape definition
	b2CircleShape l_circShape;
	l_circShape.m_radius = playerRadiusSize;

	// Main fixture attached to body represting player
	b2FixtureDef l_fixtureDef;
	l_fixtureDef.shape = &l_circShape;
	l_fixtureDef.density = mk_fDensity;
	l_fixtureDef.friction = mk_fFriction;
	l_fixtureDef.restitution = mk_fRestitution;
	l_fixtureDef.filter.categoryBits = (uint16)CollisionFilter::Player;
	l_fixtureDef.filter.maskBits = (uint16)CollisionFilter::Everything;
	l_fixtureDef.userData = (void*)((int)(FixtureType::Player));
	m_body->CreateFixture(&l_fixtureDef);	//add a fixture to the body

	// SFML shape
	m_shape.setRadius(playerRadiusSize);
	m_shape.setOrigin(playerRadiusSize, playerRadiusSize); // origin is now centre of shape (instead of top left)
	m_shape.setPosition(position);	// position set after origin changed
	m_shape.setRotation(0);
	m_shape.setFillColor(airColour);
	m_shape.setOutlineThickness(0.f);

	// Other properties
	m_speed = 1.0;
}

void Player::move(const float direction)
{
	// Move only on x-axis
	float desiredVel = direction * m_speed;
	float velChange = desiredVel - m_body->GetLinearVelocity().x;
	float impulse = m_body->GetMass() * velChange;
	m_body->ApplyLinearImpulseToCenter(b2Vec2(impulse, 0), true);
	//m_body->ApplyLinearImpulse(b2Vec2(impulse, 0), m_body->GetWorldCenter() - b2Vec2(0.01f, 0.01f), true);

	float desiredAngVel = direction * m_speed;
	float andImpulse = desiredAngVel - m_body->GetAngularVelocity();
	m_body->SetAngularVelocity(andImpulse);
}

void Player::jump()
{
	// Determine if jump is possible
	if (platformBeneath.size() <= 0) return; // player must be grounded

	// Using An Impulse
	float desiredVel = -5.0f;
	float velChange = desiredVel - m_body->GetLinearVelocity().y;
	float impulse = m_body->GetMass() * velChange;
	m_body->ApplyLinearImpulseToCenter(b2Vec2(0, impulse), true);
}

void Player::update()
{
	// Root curve equation to gradually increase speed based on game time
	float gameTime = Score::getGameTimeAsSeconds();
	m_speed = b2Clamp(sqrtf(gameTime), 4.0f, 7.0f);	// Clamp speed between param2 and param3

	// Check if player has collided with enemy:
	if (enemyCollisionCount > 0)
	{
		m_isDead = true;
		enemyCollisionCount = 0;
		return;
	}
	enemyCollisionCount = 0;

	// Update the renderable object
	b2Vec2 pos = m_body->GetPosition();
	m_shape.setPosition(pos.x, pos.y);
	float angle = m_body->GetAngle() * RAD2DEG;
	m_shape.setRotation(angle);

	// Change player colour based on whether it is grounded or not
	m_shape.setFillColor(platformBeneath.size() > 0 ? m_groundColour : m_airColour);
}

void Player::draw(RenderTarget& target, RenderStates states) const
{
	target.draw(m_shape);

	// Add a line
	RectangleShape line(Vector2f(playerRadiusSize, 0.01f));
	line.setPosition(m_shape.getPosition());
	line.setOrigin(0.f, 0.005f);
	line.rotate(m_shape.getRotation());
	line.setFillColor(Color::Magenta);
	target.draw(line);
}

void Player::resetPosition(b2Vec2& position)
{
	// The player can only be reset when it dies
	if (!m_isDead) return;

	// Set new property values for player body
	m_body->SetLinearVelocity(b2Vec2(0, 0.1f));
	m_body->SetTransform(position, 0);

	// Reset variables and score
	platformBeneath.clear();
	Score::resetCurrentScore();
	m_isDead = false;
}

void Player::startCollision(b2Fixture* thisFixture, b2Fixture* collidedWith)
{
	void* fixtureUserData = collidedWith->GetUserData();
	if (!collidedWith) return; // no user data for collision resolution

	// Collision with sensor - Determine which one
	if (collidedWith->IsSensor())
	{
		SensorType sensorType = static_cast<SensorType>((int)collidedWith->GetUserData());

		switch (sensorType)
		{
		case SensorType::WorldGround:
			m_isDead = true;
			break;

		case SensorType::EnemyHead:
			enemyCollisionCount -= 1;
			break;
		}
	}
	// Collision with a non-sensor fixture
	else
	{
		// Check for platform collision
		FixtureType fixtType = static_cast<FixtureType>((int)collidedWith->GetUserData());

		switch (fixtType)
		{
		case FixtureType::Platform:
			m_isDead = false;

			// Apply a small impulse downwards
			m_body->ApplyLinearImpulseToCenter(b2Vec2(0, 1), true);

			// This is a collision with a new platform
			if (m_lastPlatform != collidedWith)
			{
				m_lastPlatform = collidedWith;
				Score::addToScore(1);
			}

			platformBeneath.insert(collidedWith);
			break;

		case FixtureType::Enemy:
			enemyCollisionCount += 1;
			break;
		}
	}
}

void Player::endCollision(b2Fixture* thisFixture, b2Fixture* collidedWith)
{
	if (collidedWith->IsSensor()) return; // Not interested in collision with sensors

	FixtureType fixtType = static_cast<FixtureType>((int)collidedWith->GetUserData());

	if (fixtType == FixtureType::Platform)
		platformBeneath.erase(collidedWith);
}