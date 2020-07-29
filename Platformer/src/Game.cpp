/*!
\file game.cpp
*/
#include "game.h"

Game::Game()
{
	// Set the View
	m_view.setCenter(0.f, 0.f);
	m_view.setSize(m_worldSize);

	// Create a Box2D world
	m_pWorld = new b2World(mk_gravity);

	// Playable controller
	m_player = new Player(m_pWorld, Vector2f(-2.5f, -3.f));

	// Debug Draw
	m_debugDraw.setWorld(m_pWorld);

	// Texture Manager
	textures.addTexture("Background", "./assets/textures/background.png");

	// Background Image
	m_background.setSize(m_worldSize);
	m_background.setOrigin(m_worldSize / 2.0f);
	m_background.setPosition(0.0f, 0.0f);
	m_background.setTexture(textures.getTexture("Background"));

	// This could all be read in from a file, for now hard coded magic numbers
	// Shouldn't really use push back, better to pre allocate and assign
	// Infact to do this properly I should use the factory pattern with a level file parser
	// Static Game Objects
	/*m_staticBlocks.push_back(StaticBlock(m_pWorld, sf::Vector2f(0.f, 2.5f), sf::Vector2f(5.f, 0.5f), 0.f));
	m_staticBlocks.push_back(StaticBlock(m_pWorld, sf::Vector2f(-0.5f, -2.f), sf::Vector2f(4.f, 0.2f), 10.f));
	m_staticBlocks.push_back(StaticBlock(m_pWorld, sf::Vector2f(1.f, -0.5f), sf::Vector2f(5.5f, 0.2f), -10.f));
	m_staticBlocks.push_back(StaticBlock(m_pWorld, sf::Vector2f(3.8f, -1.6f), sf::Vector2f(0.2f, 1.f), -10.f));
	m_staticBlocks.push_back(StaticBlock(m_pWorld, sf::Vector2f(-3.f, 1.f), sf::Vector2f(2.5f, 0.2f), 25.f));

	m_dynamicBlocks.push_back(DynamicBlock(m_pWorld, sf::Vector2f(-1.f, 2.f), sf::Vector2f(0.1f, 0.5f), 0.f));
	m_dynamicBlocks.push_back(DynamicBlock(m_pWorld, sf::Vector2f(-0.7f, 2.f), sf::Vector2f(0.1f, 0.5f), 0.f));
	m_dynamicBlocks.push_back(DynamicBlock(m_pWorld, sf::Vector2f(-0.85f, 1.7f), sf::Vector2f(0.5f, 0.1f), 0.f));

	m_balls.push_back(DynamicCircle(m_pWorld, sf::Vector2f(-1.5f, -3.f), 0.15f, 0.f));
	m_balls.push_back(DynamicCircle(m_pWorld, sf::Vector2f(-0.85f, 1.6f), 0.1f, 0.f));

	m_dynamicBlocks.push_back(DynamicBlock(m_pWorld, sf::Vector2f(-2.5f, -3.f), sf::Vector2f(0.1f, 0.5f), 0.f));*/
	
	// border around scene and ground
	m_staticBlocks.push_back(StaticBlock(m_pWorld, sf::Vector2f(0.f, 2.5f), sf::Vector2f(8.f, 1.f), 0.f, PhysicalThing::CollisionFilter::ONE));	// ground
	m_staticBlocks.push_back(StaticBlock(m_pWorld, sf::Vector2f(-16.f, 0.f), sf::Vector2f(0.5f, 24.f), 0.f, PhysicalThing::CollisionFilter::ONE)); // left wall
	m_staticBlocks.push_back(StaticBlock(m_pWorld, sf::Vector2f(16.f, 0.f), sf::Vector2f(0.5f, 24.f), 0.f, PhysicalThing::CollisionFilter::ONE)); // right wall
	m_staticBlocks.push_back(StaticBlock(m_pWorld, sf::Vector2f(0.f, -12.f), sf::Vector2f(32.f, 0.5f), 0.f, PhysicalThing::CollisionFilter::ONE)); // top wall
	m_staticBlocks.push_back(StaticBlock(m_pWorld, sf::Vector2f(0.f, 12.f), sf::Vector2f(32.f, 0.5f), 0.f, PhysicalThing::CollisionFilter::ONE)); // bottom wall

	// Balls
	m_balls.push_back(DynamicCircle(m_pWorld, sf::Vector2f(-1.5f, -2.5f), 0.15f, 0.f, PhysicalThing::CollisionFilter::ONE));
	m_balls.push_back(DynamicCircle(m_pWorld, sf::Vector2f(0.0f, -2.f), 0.15f, 0.f, PhysicalThing::CollisionFilter::SIXTEEN));	// Middle
	m_balls.push_back(DynamicCircle(m_pWorld, sf::Vector2f(1.5f, -1.5f), 0.15f, 0.f, PhysicalThing::CollisionFilter::ONE));
	m_balls.push_back(DynamicCircle(m_pWorld, sf::Vector2f(2.5f, -2.5f), 0.15f, 0.f, PhysicalThing::CollisionFilter::ONE));

	// misc - DELETE
	clickedPointRect.setSize(Vector2f(0.1f, 0.1f));
	clickedPointRect.setPosition(0, 0);
	clickedPointRect.setFillColor(Color::Magenta);
}

Game::~Game()
{
	// Clean up all pointers
	delete m_pWorld;
	m_pWorld = nullptr;
}

void Game::update(float timestep)
{
	// Rotate player to clicked point
	b2Vec2 rotTarget(clickedPointRect.getPosition().x, clickedPointRect.getPosition().y);
	m_player->rotateTowards(rotTarget, 1 * DEG2RAD);

	// Make camera follow player
	m_view.setCenter(m_player->getPosition());

	// Update the world
	m_pWorld->Step(timestep, mk_iVelIterations, mk_iVelIterations);

	// Update each dyanmic element - effectively update render information
	for (DynamicBlock& block : m_dynamicBlocks) block.update();
	for (DynamicCircle& ball : m_balls) ball.update();
	m_player->update();

	// Delete debug shapes
	if (m_debug) m_debugDraw.clear();
}

void Game::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	// Set the view
	target.setView(m_view);

	// Draw everything
	target.draw(m_background);
	for (StaticBlock block : m_staticBlocks) target.draw(block);
	for (DynamicBlock block : m_dynamicBlocks) target.draw(block);
	for (DynamicCircle ball : m_balls) target.draw(ball);
	target.draw(*m_player);
	target.draw(clickedPointRect);	// REMOVE

	// Debug Draw
	if (m_debug) target.draw(m_debugDraw);
}

void Game::processKeyboardInput(sf::Keyboard::Key key)
{
	switch (key)
	{
		// Toggle Debug Mode
	case sf::Keyboard::Tab:	toggleDebug();	break;

		// Player Movement
	/*case Keyboard::W:	case Keyboard::Up:		m_player->move(B2UP);		break;
	case Keyboard::S:	case Keyboard::Down:	m_player->move(B2DOWN);		break;
	case Keyboard::A:	case Keyboard::Left:	m_player->move(B2LEFT);		break;
	case Keyboard::D:	case Keyboard::Right:	m_player->move(B2RIGHT);	break;*/

	// Linear Movement
	case Keyboard::A:	m_player->move(B2LEFT);				break;
	case Keyboard::S:	m_player->move(b2Vec2(0, 0));		break;
	case Keyboard::D:	m_player->move(B2RIGHT);			break;
	case Keyboard::P:	m_player->getBody()->SetTransform(b2Vec2(0, 0), 0); m_player->getBody()->SetLinearVelocity(b2Vec2(0, 0)); m_player->getBody()->SetAngularVelocity(0);	break;
		
		// Player Speed
	case sf::Keyboard::Q:	m_player->increaseSpeed(0.1f);		break;
	case sf::Keyboard::E:	m_player->increaseSpeed(-0.1f);		break;

		
	}
}

void Game::processMouseScroll(Event::MouseWheelScrollEvent scrollEvent)
{
	// Zoom in
	if (scrollEvent.delta > 0)
		m_view.zoom(zoomInFactor);
	// Zoom out
	else
		m_view.zoom(zoomOutFactor);
}

void Game::processMousePress(Event::MouseButtonEvent mouseButtonEvent, Vector2f& viewPos)
{
	// Left Button Clicked
	if (mouseButtonEvent.button == Mouse::Button::Left)
	{
		clickedPointRect.setPosition(viewPos);
		m_player->rotateTowards(b2Vec2(viewPos.x, viewPos.y));
	}
}
