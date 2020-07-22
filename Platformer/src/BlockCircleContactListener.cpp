#include "BlockCircleContactListener.h"

void BlockCircleContactListener::BeginContact(b2Contact* contact)
{
	b2Body* bodyA = contact->GetFixtureA()->GetBody();
	b2Body* bodyB = contact->GetFixtureB()->GetBody();

	std::pair<std::string, void*> dataA = *(std::pair<std::string, void*>*) bodyA->GetUserData();
	std::pair<std::string, void*> dataB = *(std::pair<std::string, void*>*) bodyB->GetUserData();

	bool isSensorA = contact->GetFixtureA()->IsSensor();
	bool isSensorB = contact->GetFixtureB()->IsSensor();

	if (isSensorA)
	{
		StaticSensor* sensor = static_cast<StaticSensor*>(bodyA->GetUserData());
		sensor->onAction(bodyB);
		return;
	}

	if (isSensorB)
	{
		StaticSensor* sensor = static_cast<StaticSensor*>(bodyB->GetUserData());
		sensor->onAction(bodyA);
		return;
	}

	// Static Block has collided with Dynamic Circle
	if (typeid(StaticBlock).name() == dataA.first)
	{
		if (typeid(DynamicCircle).name() == dataB.first)
		{
			StaticBlock* block = static_cast<StaticBlock*>(dataA.second);
			if (block != nullptr) block->setFillColor(sf::Color::Magenta);
		}
	}

	// Dynamic Circle has collided with Static Block
	if (typeid(StaticBlock).name() == dataB.first)
	{
		if (typeid(DynamicCircle).name() == dataA.first)
		{
			StaticBlock* block = static_cast<StaticBlock*>(dataB.second);
			if (block != nullptr) block->setFillColor(sf::Color::Magenta);
		}
	}

	// Dynamic Block has collided with Dynamic Circle
	if (typeid(DynamicBlock).name() == dataA.first)
	{
		if (typeid(DynamicCircle).name() == dataB.first)
		{
			DynamicBlock* block = static_cast<DynamicBlock*>(dataA.second);
			if (block != nullptr) block->setFillColor(sf::Color::Cyan);
		}
	}

	// Dynamic Circle has collided with Dynamic Block
	if (typeid(DynamicBlock).name() == dataB.first)
	{
		if (typeid(DynamicCircle).name() == dataA.first)
		{
			DynamicBlock* block = static_cast<DynamicBlock*>(dataB.second);
			if (block != nullptr) block->setFillColor(sf::Color::Cyan);
		}
	}
}

void BlockCircleContactListener::EndContact(b2Contact* contact)
{
	b2Body* bodyA = contact->GetFixtureA()->GetBody();
	b2Body* bodyB = contact->GetFixtureB()->GetBody();

	std::pair<std::string, void*> dataA = *(std::pair<std::string, void*>*) bodyA->GetUserData();
	std::pair<std::string, void*> dataB = *(std::pair<std::string, void*>*) bodyB->GetUserData();

	if (typeid(StaticBlock).name() == dataA.first)
	{
		if (typeid(DynamicCircle).name() == dataB.first)
		{
			StaticBlock* block = static_cast<StaticBlock*>(dataA.second);
			if (block != nullptr) block->setFillColor(sf::Color::Green);
		}
	}

	if (typeid(StaticBlock).name() == dataB.first)
	{
		if (typeid(DynamicCircle).name() == dataA.first)
		{
			StaticBlock* block = static_cast<StaticBlock*>(dataB.second);
			if (block != nullptr) block->setFillColor(sf::Color::Green);
		}
	}

	if (typeid(DynamicBlock).name() == dataA.first)
	{
		if (typeid(DynamicCircle).name() == dataB.first)
		{
			DynamicBlock* block = static_cast<DynamicBlock*>(dataA.second);
			if (block != nullptr) block->setFillColor(sf::Color::Red);
		}
	}

	if (typeid(DynamicBlock).name() == dataB.first)
	{
		if (typeid(DynamicCircle).name() == dataA.first)
		{
			DynamicBlock* block = static_cast<DynamicBlock*>(dataB.second);
			if (block != nullptr) block->setFillColor(sf::Color::Red);
		}
	}
}
