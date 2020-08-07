#include "WorldGenerator.h"

set<Platform*> WorldGenerator::m_platToDestory; // initialise public static variable

WorldGenerator::WorldGenerator(b2World* world, View& view) : m_world(world)
{
	Vector2f viewSize = view.getSize();
	Vector2f viewPos = view.getCenter();
	float xDiff = (viewSize.x * 0.5f) + 0.5f; // A point slightly past the centre of view

	// Create the Physics body:
	b2BodyDef l_bodyDef;
	l_bodyDef.type = b2_dynamicBody; // Required for collision
	l_bodyDef.gravityScale = 0;
	l_bodyDef.position.Set(viewPos.x, viewPos.y);
	l_bodyDef.angle = 0;
	m_body = world->CreateBody(&l_bodyDef);

	// Create a physics shape to attach to both fixtures
	b2PolygonShape l_shape;
	l_shape.m_radius = 0;

	// Create a fixture definition common for both fixtures
	b2FixtureDef l_fixtureDef;
	l_fixtureDef.shape = &l_shape;
	l_fixtureDef.isSensor = true;

	// Modify, create and attach the destructor fixture:
	float xPos = viewPos.x - xDiff;
	l_shape.SetAsBox(0.5f, viewSize.y, b2Vec2(xPos, viewPos.y), 0);
	m_destructorFixture = m_body->CreateFixture(&l_fixtureDef);
	m_destructorFixture->SetUserData((void*)(int)FixtureType::Destructor);

	// Modify, create and attach the creator fixture:
	xPos = viewPos.x + xDiff;
	l_shape.SetAsBox(0.5f, viewSize.y, b2Vec2(xPos, viewPos.y), 0);
	m_creatorFixture = m_body->CreateFixture(&l_fixtureDef);
	m_creatorFixture->SetUserData((void*)(int)FixtureType::Creator);
}

void WorldGenerator::setUserData(void* userData)
{
	if (!userData)
		m_body->SetUserData(new pair<string, void*>(typeid(WorldGenerator).name(), this));
	else
		m_body->SetUserData(userData);
}

void WorldGenerator::update(View& view)
{
	m_body->SetLinearVelocity(b2Vec2(m_speed, 0));
	b2Vec2 pos = m_body->GetPosition();
	view.setCenter(pos.x, pos.y);

	// Check if anything needs to be destroyed: (Consider making an abstract class called destoryable which can be inherited)
	for (auto it = WorldGenerator::m_platToDestory.begin(); it != WorldGenerator::m_platToDestory.end(); it++)
	{
		Platform* platform = *it;
		b2Body* body = (*it)->getBody(); // consider using destructor to destory body instead
		m_world->DestroyBody(body);
		m_platforms.erase(platform);
		delete platform;
	}
	WorldGenerator::m_platToDestory.clear();
}

void WorldGenerator::onAction(b2Fixture* whatFixture, b2Fixture* collissionStartedWith)
{
}

void WorldGenerator::offAction(b2Fixture* whatFixture, b2Fixture* collisionEndedWith)
{
	// For now only handling destructor
	if (whatFixture != m_destructorFixture) return;

	void* collisionWithUserData = collisionEndedWith->GetBody()->GetUserData();
	if (collisionWithUserData)
	{
		pair<string, void*> userData = *((pair<string, void*>*) collisionWithUserData);
		if (userData.first == typeid(Platform).name())
		{
			Platform* platform = static_cast<Platform*>(userData.second);
			m_platToDestory.insert(platform);
			m_platToDestory.insert(platform);
		}
	}
}
