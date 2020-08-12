#pragma once

/*!
\file EnemyPlatform.h
*/

#include <Box2D/Box2D.h>
#include <SFML/Graphics.hpp>

#include "World.h"
#include "Platform.h"
#include "Enemy.h"

/*! \class EnemyPlatform
\brief A platform which generates an enemy on it
*/

class EnemyPlatform : public Platform
{
private:
	Enemy* m_enemy;

public:
	EnemyPlatform(b2World* world,
		Vector2f& position = Vector2f(0, 0),
		Vector2f& size = Vector2f(10.0f, 0.4f),
		const Color colour = Color::Green
	); //!< Complete contructor with default parameters
	~EnemyPlatform();

	void update(); //!< Update platform attributes (e.g. Size, position, colour)
	void draw(RenderTarget& target, RenderStates states) const; //!< Overide base function to allow drawing of Platform objects
};