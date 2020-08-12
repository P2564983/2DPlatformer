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

	// Debug Draw
	m_debugDraw.setWorld(m_pWorld);

	// Texture Manager
	textures.addTexture("Background", "./assets/textures/cloud_background.png");

	// Background Image
	m_background.setSize(m_worldSize);
	m_background.setOrigin(m_worldSize / 2.0f);
	m_background.setPosition(0.0f, 0.0f);
	m_background.setTexture(textures.getTexture("Background"));

	// Test
	m_debugGrid = new DebugGrid(m_view); // Remember to CLEAN UP with DELETE
	m_worldGenerator = new WorldGenerator(m_pWorld, m_view);
	m_worldGenerator->setUserData();
	// Playable controller
	m_player = m_worldGenerator->getPlayer();

	// Set Contact Listeners
	// ToDo: You can only have one contact listener - merge all listeners into one
	m_pWorld->SetContactListener(&m_contactListener); // The Player/Ground Contact Listener

	// User Interface
	m_userInterface = new UserInterface();
}

Game::~Game()
{
	delete m_debugGrid;

	// Clean up all pointers
	delete m_pWorld;
	m_pWorld = nullptr;

	delete m_userInterface;
	m_userInterface = nullptr;

	delete m_worldGenerator; // This also deletes m_player
	m_worldGenerator = nullptr;

	delete m_debugGrid;
	m_debugGrid = nullptr;
}

void Game::update(float timestep)
{
	// Make camera follow World Generator
	Vector2f viewPos = m_worldGenerator->getPositionV2F();
	m_view.setCenter(viewPos);
	m_background.setPosition(viewPos); // Keep the background in view

	// Update the world
	m_pWorld->Step(timestep, mk_iVelIterations, mk_iVelIterations);

	// Update the world
	m_worldGenerator->update();
	if (m_debugGridDraw) m_debugGrid->update(m_view);
	m_userInterface->update();

	// Delete debug shapes
	if (m_debug) m_debugDraw.clear();

}

void Game::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	// Set the view
	target.setView(m_view);

	// Draw everything
	target.draw(m_background);
	target.draw(*m_worldGenerator);
	target.draw(*m_userInterface);

	// Debug Draw
	if (m_debugGridDraw) target.draw(*m_debugGrid);
	if (m_debug) target.draw(m_debugDraw);
}

void Game::processKeyboardInput(sf::Keyboard::Key key, bool pressed)
{
	// Actions to take when a button is pressed:
	if (pressed)
	{
		switch (key)
		{
		// Toggle Debug Mode
		case sf::Keyboard::Tab:	m_debug = !m_debug;					break;

		// Toggle Debug Grid Mode
		case sf::Keyboard::G:	m_debugGridDraw = !m_debugGridDraw;	break;

			// Toggle Camera Zoom capability (to see world generator)
		case sf::Keyboard::Z:	allowCameraZoom = !allowCameraZoom;	break;

		// Player jump
		case sf::Keyboard::W:
			if (m_player) m_player->jump();
			break;
		}
	}
	// Actions to take when a button is released:
	else
	{
		switch (key)
		{
		}
	}
}

void Game::processMouseScroll(Event::MouseWheelScrollEvent scrollEvent)
{
	if(allowCameraZoom)
		m_view.zoom((scrollEvent.delta > 0) ? zoomInFactor : zoomOutFactor);
}

void Game::processMousePress(Event::MouseButtonEvent mouseButtonEvent, Vector2f& viewPos)
{
	// Left Button Clicked
	if (mouseButtonEvent.button == Mouse::Button::Left) {}
}
