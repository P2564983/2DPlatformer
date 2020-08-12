#include "WorldGenerator.h"

WorldGenerator::WorldGenerator(b2World* world, View& view) : m_b2World(world)
{
	m_viewSize = view.getSize();
	Vector2f viewPos = view.getCenter();
	float xOffset = (m_viewSize.x * 0.5f) + 0.5f; // A point slightly past the view border
	centreYPosition = viewPos.y;
	minYPosition = viewPos.y + m_viewSize.y * 0.5f - maxPlatHeight;
	maxYPosition = viewPos.y - m_viewSize.y * 0.5f + maxPlatHeight + 1.0f;

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

	// Create a fixture definition common for sensor fixtures
	b2FixtureDef l_fixtureDef;
	l_fixtureDef.shape = &l_shape;
	l_fixtureDef.isSensor = true;

	// Modify, create and attach the destructor fixture:
	float xPos = viewPos.x - xOffset;
	l_shape.SetAsBox(0.1f, m_viewSize.y, b2Vec2(xPos, viewPos.y), 0);
	m_destructorSensor = m_body->CreateFixture(&l_fixtureDef);
	m_destructorSensor->SetUserData((void*)(int)SensorType::WorldDestructor);

	// Modify, create and attach the creator fixture:
	xPos = viewPos.x + xOffset;
	l_shape.SetAsBox(0.1f, m_viewSize.y, b2Vec2(xPos, viewPos.y), 0);
	m_creatorSensor = m_body->CreateFixture(&l_fixtureDef);
	m_creatorSensor->SetUserData((void*)(int)SensorType::WorldCreator);

	// Modify, create and attach the ground fixture:
	l_shape.SetAsBox(m_viewSize.x * 0.5f, 0.1f, b2Vec2(0, viewPos.y + m_viewSize.y * 0.5f + 0.05f), 0);
	l_fixtureDef.userData = (void*)(int)SensorType::WorldGround;
	m_groundSensor = m_body->CreateFixture(&l_fixtureDef);

	// Generate a player into the world at centre position:
	m_worldObjects.insert(m_player = new Player(m_b2World, viewPos, Color::Black));

	// Generate an initial platform 1.5x the view size placed under the player:
	Vector2f platPos(viewPos.x, viewPos.y + m_viewSize.y * 0.25f);
	Vector2f platSize(m_viewSize.x * 1.5f, 0.4f);
	m_worldObjects.insert(new Platform(m_b2World, platPos, platSize));

	// Other setup
	for (auto objects : m_worldObjects) objects->setUserData(); // Set the user data for all objects
	lastPlatPos = Vector2f(platPos.x + platSize.x * 0.5f, platPos.y); // Store where the last platform is
	srand((unsigned)time(0)); // Use current time as seed for random generator (used to place objects at random positions)
}

WorldGenerator::~WorldGenerator()
{
	delete m_player;
	m_player = nullptr;

	for (auto objects : m_worldObjects) delete objects;
	m_worldObjects.clear();
}

void WorldGenerator::resetWorld()
{
	// Destory all the existing platforms:
	for (auto object : m_worldObjects)
	{
		if(object != m_player)
			delete object;
	}
	m_worldObjects.clear();
	m_worldObjects.insert(m_player);

	// Generate an initial platform 1.5x the view size:
	Vector2f platPos(m_player->getPositionB2().x, centreYPosition + m_viewSize.y * 0.25f);
	Vector2f platSize(m_viewSize.x * 1.5f, 0.4f);
	m_worldObjects.insert(new Platform(m_b2World, platPos, platSize));
	lastPlatPos = Vector2f(platPos.x + platSize.x * 0.5f, platPos.y); // Store where the last platform is

	m_player->resetPosition(b2Vec2(m_player->getPositionB2().x, centreYPosition));
}

void WorldGenerator::update()
{
	if (m_player->isDead()) resetWorld();
	else m_player->move(b2Vec2(1, 0));

	b2Vec2 targetVel = b2Vec2(m_player->getPositionB2().x - m_body->GetPosition().x, 0); // A vector going from WorldGenerator.x to Player.x 
	targetVel.x += (m_viewSize.y * 0.5f);
	m_body->SetLinearVelocity(m_speed * targetVel); // (only x vel is ever changed)

	// Check if anything needs to be destroyed:
	for (auto it = m_toDestroy.begin(); it != m_toDestroy.end(); it++)
	{
		PhysicalThing* destroyable = *it;
		m_worldObjects.erase(destroyable);
		delete destroyable; // This free's memory and deletes body of platform too
	}
	m_toDestroy.clear();

	// Check if anything needs to be generated:
	if (needToGenerate || m_worldObjects.size() <= 3)
	{
		PlatformType platType = (PlatformType)(rand() % (int)PlatformType::Count); // Number within range of 0 and and platform count
		generatePlatform(platType);
	}

	// Update all PhysicalThings
	for (auto worldObject : m_worldObjects) worldObject->update();
}

void WorldGenerator::generatePlatform(PlatformType platType)
{
	//platType = PlatformType::Enemy;

	PhysicalThing* newPlatform = nullptr;
	Vector2f newPos, platformSize;

	// Randomly generate platform size
	// Random floating point number between min/max platform width
	platformSize.x = ((rand() % (int)((maxPlatWidth - minPlatWidth) * 10 + 1)) / 10.0f) + minPlatWidth;
	// Random floating point number between min/max platform height
	platformSize.y = ((rand() % (int)((maxPlatHeight - minPlatHeight) * 100 + 1)) / 100.0f) + minPlatHeight;

	// Generate platform position:
	Vector2f positionOffset;
	// position.x is based on width and a randomly generated padding
	float paddingX = ((rand() % (int)((maxPaddingX - minPaddingX) * 100 + 1)) / 100.0f) + minPaddingX;
	positionOffset.x = platformSize.x * 0.5f + paddingX;
	// position.y is based on height and a randomly generated padding (within constraint)
	float yLimits = 2 - platformSize.y;
	positionOffset.y = ((rand() % (int)((yLimits) * 100 + 1)) / 100.0f) - (yLimits * 0.5f);

	//newPos = lastPlatPos + Vector2f(platformSize.x * 0.5f + padding, yChange);
	newPos = lastPlatPos + positionOffset;

	// Platform position too high
	if (newPos.y < maxYPosition) newPos.y = centreYPosition;
	// Platform position too low
	if (newPos.y > minYPosition) newPos.y = lastPlatPos.y - (1 - platformSize.y);

	switch (platType)
	{
	default:
	case PlatformType::Normal:
		newPlatform = new Platform(m_b2World, newPos, platformSize);
		break;

	case PlatformType::Coin:
		newPlatform = new CoinPlatform(m_b2World, newPos, platformSize);
		break;

	case PlatformType::Enemy:
		newPlatform = new EnemyPlatform(m_b2World, newPos, platformSize);
		break;

	case PlatformType::Revolute:
		newPlatform = new RevolutePlatform(m_b2World, newPos, platformSize);
		break;
	}

	// Insert the newly generated platfrom into a list of objects and set its user data:
	if (newPlatform) (*m_worldObjects.insert(newPlatform).first)->setUserData();
	needToGenerate = false;
	lastPlatPos = newPos + Vector2f(platformSize.x * 0.5f, 0);
}

void WorldGenerator::startCollision(b2Fixture* whatFixture, b2Fixture* collisionStartedWith)
{
	// This function handles creation of platforms
	needToGenerate = false;

	// Check if platform needs to be generated:
	if (whatFixture != m_creatorSensor || !collisionStartedWith->IsSensor()) return;

	// Platforms are only created when the creator sensor collides with a platform end sensor
	void* userData = collisionStartedWith->GetUserData();
	if (!userData) return;
	if (static_cast<SensorType>((int)userData) == SensorType::PlatformEnd) needToGenerate = true;
}

void WorldGenerator::endCollision(b2Fixture* whatFixture, b2Fixture* collisionEndedWith)
{
	// This function handles destruction of PhysicalThings
	// Check if destructor collided with a sensor:
	if (whatFixture != m_destructorSensor || !collisionEndedWith->IsSensor()) return;

	// Destruction only occurs at the end of a platform (via platform end collision sensor)
	void* fixtData = collisionEndedWith->GetUserData();
	if (static_cast<SensorType>((int)fixtData) != SensorType::PlatformEnd) return;

	// Destroy the PhysicalThing the sensor is attached to:
	void* bodyUserData = collisionEndedWith->GetBody()->GetUserData();
	if (!bodyUserData) return;
	pair<string, void*> userData = *((pair<string, void*>*) bodyUserData);
	if (userData.first == typeid(PhysicalThing).name())
		m_toDestroy.insert(static_cast<PhysicalThing*>(userData.second)); // Add this object to the list of items to destroy
}

void WorldGenerator::draw(RenderTarget& target, RenderStates states) const
{
	// Draw all PhysicalThing objects
	for (auto worldObject : m_worldObjects) target.draw(*worldObject);
}