#include "..\include\Enemy.h"

Enemy::Enemy(b2World* world, Platform* platformOn, Color colour) : m_platform(platformOn)
{
	b2Vec2 platPos = platformOn->getPositionB2();
	Vector2f platSize = platformOn->getSize();
	Vector2f enemyPos = Vector2f(platPos.x, platPos.y - (platSize.y * 0.5f) - enemyHalfSize.y);

	//set up a dynamic body
	b2BodyDef bodyDef;
	bodyDef.type = b2_dynamicBody;
	bodyDef.position.Set(enemyPos.x, enemyPos.y);
	m_body = world->CreateBody(&bodyDef);
	m_body->SetFixedRotation(true); // prevent rotation

	//prepare a shape definition
	b2PolygonShape shape;
	//shape.SetAsBox(0.25f, 0.25f);
	shape.SetAsBox(enemyHalfSize.x, enemyHalfSize.y);
	shape.m_radius = 0;

	// Main fixture attached to body represting enemy
	b2FixtureDef l_fixtureDef;
	l_fixtureDef.shape = &shape;
	l_fixtureDef.density = 1;
	l_fixtureDef.friction = mk_fFriction;
	l_fixtureDef.restitution = 0;
	// Setup collision filtering:
	l_fixtureDef.filter.categoryBits = (uint16)CollisionFilter::Enemy;
	l_fixtureDef.filter.maskBits = (uint16)CollisionFilter::Platform | (uint16)CollisionFilter::Player;
	m_body->CreateFixture(&l_fixtureDef)->SetUserData((void*)(int)FixtureType::Enemy);	//add a fixture to the body and sets fixtures user data

	// Smaller fixture attached to body head used to determine collision from above
	shape.SetAsBox(sensorHalfSize.x, sensorHalfSize.y, b2Vec2(0, -enemyHalfSize.y + sensorHalfSize.y), 0);
	l_fixtureDef.isSensor = true;
	l_fixtureDef.density = l_fixtureDef.friction = l_fixtureDef.restitution = 0;
	l_fixtureDef.filter.maskBits = (uint16)CollisionFilter::Player; // Head sensor only collides with player
	l_fixtureDef.userData = (void*)(int)SensorType::EnemyHead;
	m_headSensorFixture = m_body->CreateFixture(&l_fixtureDef);

	// SFML shape representing enemy
	m_enemyShape.setSize(Vector2f(enemyHalfSize.x * 2, enemyHalfSize.y * 2));
	m_enemyShape.setOrigin(enemyHalfSize.x, enemyHalfSize.y); // origin is now centre of shape (instead of top left)
	m_enemyShape.setPosition(enemyPos);	// position set after origin changed
	m_enemyShape.setRotation(0);
	m_enemyShape.setFillColor(colour);
	m_enemyShape.setOutlineThickness(0.f);

	// Other properties
	m_velocity = 1.5f;
}

Enemy::~Enemy()
{
	// PhysicalThing destructor will destroy the body (if it has not already been)
	m_headSensorFixture = nullptr;
	m_platform = nullptr;
}

void Enemy::move()
{
	// Move only on x-axis
	float velToApply = m_velocity - m_body->GetLinearVelocity().x; // target speed - current speed
	float impulse = m_body->GetMass() * velToApply;
	m_body->ApplyLinearImpulseToCenter(b2Vec2(impulse, 0), true);
}

void Enemy::update()
{
	// It may be possible that this enemy has been killed but this object is still accessible:
	if (!m_body) return;

	// Player has just been killed
	if (m_isDead)
	{
		// Destory this enemy from the physics world
		m_body->GetWorld()->DestroyBody(m_body);
		m_body = nullptr;
		return;
	}

	move();

	b2Vec2 pos = m_body->GetPosition();
	m_enemyShape.setPosition(pos.x, pos.y);

	float angle = m_body->GetAngle() * RAD2DEG;
	m_enemyShape.setRotation(angle);
}

void Enemy::draw(RenderTarget& target, RenderStates states) const
{
	if (m_body)	target.draw(m_enemyShape);
}

bool Enemy::isDead() const
{
	int i = 0;
	return m_isDead;
}

void Enemy::startCollision(b2Fixture* thisFixture, b2Fixture* collidedWith)
{
	void* collidedWithUserData = collidedWith->GetUserData();

	// Check if enemy has collided with platform border:
	if (collidedWith->IsSensor())
	{
		SensorType sensorType = (SensorType)((int)collidedWithUserData);
		switch (sensorType)
		{
		default:
		case SensorType::Undefined:
			break;

		// Enemy has collided with platform edge - change direction
		case SensorType::PlatformStart:
		case SensorType::PlatformEnd:
			m_velocity *= -1; // changes direction but maintains same speed
			break;

		// Collision with player base
		//case SensorType::PlayerFoot:
		//	// Collision from above
		//	if (thisFixture == m_headSensorFixture) m_isDead = true;
		//	break;
		}
	}
	else
	{
		FixtureType fixtType = (FixtureType)((int)collidedWithUserData);
		switch (fixtType)
		{
		case FixtureType::Player:
			if (thisFixture == m_headSensorFixture)
			{
				m_isDead = true;
				Score::addToScore(2);
			}
			break;
		}
	}
}
