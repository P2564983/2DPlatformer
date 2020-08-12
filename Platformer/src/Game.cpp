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
	
	// misc - DELETE
	clickedPointRect.setSize(Vector2f(0.1f, 0.1f));
	clickedPointRect.setPosition(0, 0);
	clickedPointRect.setFillColor(Color::Magenta);
	playerMoveDirection = b2Vec2(0, 0);

	// Test
	m_debugGrid = new DebugGrid(m_view); // Remember to CLEAN UP with DELETE
	m_worldGenerator = new WorldGenerator(m_pWorld, m_view);
	m_worldGenerator->setUserData();
	// Playable controller
	m_player = m_worldGenerator->getPlayer();

	// Set Contact Listeners
	// ToDo: You can only have one contact listener - merge all listeners into one
	m_pWorld->SetContactListener(&playerGroundCL); // The Player/Ground Contact Listener

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

	delete m_worldGenerator;
	m_worldGenerator = nullptr;

	// TODO Clean up all pointers
}

void Game::update(float timestep)
{
	// Move player based on keyboard input (using playerMoveDirection):
	processPlayerMovement();
	//m_player->move(b2Vec2(playerMoveDirection.x, 0)); // This is now controlled by WorldGenerator
	if (playerMoveDirection.y < 0) m_player->jump(); // -value means jump

	// Make camera follow World Generator
	Vector2f viewPos = m_worldGenerator->getPositionV2F();
	m_view.setCenter(viewPos);
	m_background.setPosition(viewPos);

	// Update the world
	m_pWorld->Step(timestep, mk_iVelIterations, mk_iVelIterations);

	// Update each dyanmic element - effectively update render information
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
	if (m_debugGridDraw) target.draw(*m_debugGrid);
	target.draw(*m_worldGenerator);
	target.draw(clickedPointRect);	// REMOVE
	target.draw(*m_userInterface);

	// Debug Draw
	if (m_debug) target.draw(m_debugDraw);
}

// This method helps smooth player movement
void Game::processPlayerMovement()
{
	playerMoveDirection = b2Vec2(0, 0); // Reset 
	// Move up
	if (Keyboard::isKeyPressed(Keyboard::Key::W))
		playerMoveDirection.y -= 1;
	//// Move down
	//if (Keyboard::isKeyPressed(Keyboard::Key::S))
	//	playerMoveDirection.y += 1;
	//// Move left
	//if (Keyboard::isKeyPressed(Keyboard::Key::A))
	//	playerMoveDirection.x -= 1;
	//// Move right
	if (Keyboard::isKeyPressed(Keyboard::Key::D))
		playerMoveDirection.x += 1;

	// Constrain movement
	playerMoveDirection.x = fmaxf(-1.0, fminf(1.0, playerMoveDirection.x));
	playerMoveDirection.x = fmaxf(-1.0, fminf(1.0, playerMoveDirection.x));
}

void Game::processKeyboardInput(sf::Keyboard::Key key, bool pressed)
{

	b2MassData massData; // REMOVE TEST

	// Actions to take when a button is preesed:
	if (pressed)
	{
		switch (key)
		{
			// Toggle Debug Mode
		case sf::Keyboard::Tab:	toggleDebug();	break;
			// Toggle Debug Grid Mode
		case sf::Keyboard::G:	m_debugGridDraw = !m_debugGridDraw;	break;

			// Player Speed
		case sf::Keyboard::Q:	m_player->increaseSpeed(0.1f);		break;
		case sf::Keyboard::E:	m_player->increaseSpeed(-0.1f);		break;

			// misc
		/*case Keyboard::P:
			m_player->getBody()->SetTransform(b2Vec2(0, 0), 0);
			m_player->getBody()->SetLinearVelocity(b2Vec2(0, 0));
			m_player->getBody()->SetAngularVelocity(0);
			break;

		case Keyboard::Z:
			m_player->getBody()->GetMassData(&massData);
			massData.mass -= 0.25f;
			m_player->getBody()->SetMassData(&massData);
			break;

		case Keyboard::X:
			m_player->getBody()->GetMassData(&massData);
			massData.mass += 0.25f;
			m_player->getBody()->SetMassData(&massData);
			break;*/
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
	m_view.zoom((scrollEvent.delta > 0) ? zoomInFactor : zoomOutFactor);
}

void Game::processMousePress(Event::MouseButtonEvent mouseButtonEvent, Vector2f& viewPos)
{
	// Left Button Clicked
	if (mouseButtonEvent.button == Mouse::Button::Left)
	{
		clickedPointRect.setPosition(viewPos);
		//m_player->rotateTowards(b2Vec2(viewPos.x, viewPos.y));
		//m_player->getBody()->SetTransform(b2Vec2(viewPos.x, viewPos.y), 0);
		//m_player->getBody()->ApplyForceToCenter(b2Vec2(0.01f, 0.01f), true); // apply a tiny force to wake body
	}
}
