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
	m_player = new Player(m_pWorld, Vector2f(-13.0f, 9.3f), Color::Black);

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
	m_staticBlocks.reserve(5);
	m_staticBlocks.push_back(StaticBlock(m_pWorld, sf::Vector2f(-16.f, 0.f), sf::Vector2f(0.5f, 24.f), 0.f, PhysicalThing::CollisionFilter::ONE)); // left wall
	m_staticBlocks.push_back(StaticBlock(m_pWorld, sf::Vector2f(16.f, 0.f), sf::Vector2f(0.5f, 24.f), 0.f, PhysicalThing::CollisionFilter::ONE)); // right wall
	m_staticBlocks.push_back(StaticBlock(m_pWorld, sf::Vector2f(0.f, -12.f), sf::Vector2f(32.f, 0.5f), 0.f, PhysicalThing::CollisionFilter::ONE)); // top wall
	m_staticBlocks.push_back(StaticBlock(m_pWorld, sf::Vector2f(0.f, 12.f), sf::Vector2f(32.f, 0.5f), 0.f, PhysicalThing::CollisionFilter::ONE)); // bottom wall
	// Some platforms:
	m_staticBlocks.push_back(StaticBlock(m_pWorld, sf::Vector2f(-13, 10), sf::Vector2f(2, 0.4f), 0.f, PhysicalThing::CollisionFilter::ONE));
	m_staticBlocks.push_back(StaticBlock(m_pWorld, sf::Vector2f(-10, 9), sf::Vector2f(2.f, 0.4f), 0.f, PhysicalThing::CollisionFilter::ONE));
	m_staticBlocks.push_back(StaticBlock(m_pWorld, sf::Vector2f(-7, 8), sf::Vector2f(2.f, 0.4f), 0.f, PhysicalThing::CollisionFilter::ONE));
	m_staticBlocks.push_back(StaticBlock(m_pWorld, sf::Vector2f(-4, 7), sf::Vector2f(2.f, 0.4f), 0.f, PhysicalThing::CollisionFilter::ONE));


	// Balls
	//m_balls.reserve(5);
	//m_balls.push_back(DynamicCircle(m_pWorld, sf::Vector2f(-1.5f, -2.5f), 0.15f, 0.f, PhysicalThing::CollisionFilter::ONE));
	//m_balls.push_back(DynamicCircle(m_pWorld, sf::Vector2f(0.0f, -2.f), 0.15f, 0.f, PhysicalThing::CollisionFilter::SIXTEEN));	// Middle
	//m_balls.push_back(DynamicCircle(m_pWorld, sf::Vector2f(1.5f, -1.5f), 0.15f, 0.f, PhysicalThing::CollisionFilter::ONE));
	//m_balls.push_back(DynamicCircle(m_pWorld, sf::Vector2f(2.5f, -2.5f), 0.15f, 0.f, PhysicalThing::CollisionFilter::ONE));
	m_balls.push_back(DynamicCircle(m_pWorld, sf::Vector2f(-10.0f, 1.0f), 0.15f, 0.f, PhysicalThing::CollisionFilter::ONE));

	// Collectibles
	m_coins.reserve(2);
	m_coins.push_back(new Coin(m_pWorld, Vector2f(-13, 11.5f))); // memory leak?
	m_coins.push_back(new Coin(m_pWorld, Vector2f(-10, 11.5f))); // memory leak?

	// Rotating Platforms:
	m_rotPlatforms.reserve(1);
	m_rotPlatforms.push_back(new RotatingPlatform(m_pWorld, Vector2f(5, 6), Color::Blue));

	// misc - DELETE
	clickedPointRect.setSize(Vector2f(0.1f, 0.1f));
	clickedPointRect.setPosition(0, 0);
	clickedPointRect.setFillColor(Color::Magenta);
	playerMoveDirection = b2Vec2(0, 0);

	// Update User Data
	m_player->setUserData();
	for (Coin* coin : m_coins) coin->setUserData();

	// Set Contact Listeners
	// ToDo: You can only have one contact listener - merge all listeners into one
	m_pWorld->SetContactListener(&coinPlayerCL); // The Coin/Player Contact Listener
	m_pWorld->SetContactListener(&playerGroundCL); // The Player/Ground Contact Listener
}

Game::~Game()
{
	// Clean up all pointers
	delete m_pWorld;
	m_pWorld = nullptr;
}

void Game::update(float timestep)
{
	// Move player based on keyboard input (using playerMoveDirection):
	processPlayerMovement();
	m_player->move(b2Vec2(playerMoveDirection.x, 0));
	if (playerMoveDirection.y < 0) m_player->jump(); // -value means jump
	// ToDo: Implement jump down

	// Make camera follow player
	m_view.setCenter(m_player->getPosition());

	// Update the world
	m_pWorld->Step(timestep, mk_iVelIterations, mk_iVelIterations);

	// Check if anything needs to be destroyed: (Consider making an abstract class called destoryable which can be inherited)
	for (auto it = m_coins.begin(); it != m_coins.end(); )
	{
		// Object need not be destoryed, continue loop
		if (!(*it)->destroy())
		{
			it++;
			continue;
		}

		// Remove from vector list (destroy() method above already removes body from box2d physics world):
		if (it == m_coins.begin())
		{
			m_coins.erase(it);
			it = m_coins.begin();
		}
		else
		{
			vector<Coin*>::iterator prev = it - 1;
			m_coins.erase(it);
			it = prev + 1;
		}


	}
	
	// Update each dyanmic element - effectively update render information
	for (DynamicBlock& block : m_dynamicBlocks) block.update();
	for (DynamicCircle& ball : m_balls) ball.update();
	for (RotatingPlatform* plat : m_rotPlatforms) plat->update();
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
	for (Coin* coin : m_coins) target.draw(*coin);
	for (RotatingPlatform* platform : m_rotPlatforms) target.draw(*platform);
	target.draw(*m_player);
	target.draw(clickedPointRect);	// REMOVE

	// Debug Draw
	if (m_debug) target.draw(m_debugDraw);
}

// This method helps smooth player movement
void Game::processPlayerMovement()
{
	playerMoveDirection = b2Vec2(0, 0);
	// Move up
	if (Keyboard::isKeyPressed(Keyboard::Key::W))
		playerMoveDirection.y -= 1;
	// Move down
	if (Keyboard::isKeyPressed(Keyboard::Key::S))
		playerMoveDirection.y += 1;
	// Move left
	if (Keyboard::isKeyPressed(Keyboard::Key::A))
		playerMoveDirection.x -= 1;
	// Move right
	if (Keyboard::isKeyPressed(Keyboard::Key::D))
		playerMoveDirection.x += 1;
}

void Game::processKeyboardInput(sf::Keyboard::Key key, bool pressed)
{
	// Actions to take when a button is preesed:
	if (pressed)
	{
		switch (key)
		{
		// Toggle Debug Mode
		case sf::Keyboard::Tab:	toggleDebug();	break;
		
		// Player Speed
		case sf::Keyboard::Q:	m_player->increaseSpeed(0.1f);		break;
		case sf::Keyboard::E:	m_player->increaseSpeed(-0.1f);		break;

		// misc
		case Keyboard::P:	
			m_player->getBody()->SetTransform(b2Vec2(0, 0), 0); 
			m_player->getBody()->SetLinearVelocity(b2Vec2(0, 0)); 
			m_player->getBody()->SetAngularVelocity(0);	
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
	m_view.zoom((scrollEvent.delta > 0) ? zoomInFactor : zoomOutFactor);
	return;

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
		//m_player->rotateTowards(b2Vec2(viewPos.x, viewPos.y));
		m_player->getBody()->SetTransform(b2Vec2(viewPos.x, viewPos.y), 0);
		m_player->getBody()->ApplyForceToCenter(b2Vec2(0.01f, 0.01f), true); // apply a tiny force to wake body
	}
}
