#pragma once

/*!
\file game.h
*/

#include <Box2D/Box2D.h>
#include <SFML/Graphics.hpp>
#include <vector>

#include "StaticBlock.h"
#include "DynamicBlock.h"
#include "DynamicCircle.h"
#include "Player.h"
#include "World.h"
#include "Coin.h"
#include "CoinPlayerContactListener.h"
#include "PlayerGroundContactListener.h"
#include "RotatingPlatform.h"

#include "SFMLDebugDraw.h"
#include "TextureManager.h"

using namespace sf;
using namespace std;

/*! \class Game
\brief Holds all information about the game, blocks, balls etc and allows updating and rendering.
*/

class Game : public Drawable
{
private:
	Vector2f m_worldSize = Vector2f(8.0f, 6.0f); //!< Size of the physical world in meters (8x6)
	View m_view; //!< The view used for rendering (maps physical co-ordinates ^ to rendering (SFML) co-ordinates)

	// Box2D:
	b2World* m_pWorld = nullptr; //!< Pointer to the Box2D world. Using pointers as BOX2D has it's own memory management.
	const int mk_iVelIterations = 7; //!< On each update there will be 7 velocity iterations in the physics engine
	const int mk_iPosIterations = 5; //!< On each update there will be 5 position iterations
	const b2Vec2 mk_gravity = b2Vec2(0.f, 9.81f); //!< Standard earth gravity will be used

	// Objects within the world
	sf::RectangleShape m_background; //!< Background of the world
	Player* m_player; //!< The controllable actor in the world
	vector<StaticBlock> m_staticBlocks; //!< A collection of fixed blocks. 
	vector<DynamicBlock> m_dynamicBlocks; //!< A collection of moving blocks. 
	vector<DynamicCircle> m_balls; //!< A collection of moving balls. 
	vector<Coin*> m_coins; //!< A collection of collectible coins.
	vector<RotatingPlatform*> m_rotPlatforms; //!< A collection of rotating platforms.

	// Texture Manager
	TextureManager textures;		//!< Manages all textures

	// Contact Listeners
	CoinPlayerContactListener coinPlayerCL;
	PlayerGroundContactListener playerGroundCL;

	bool m_debug = false; //!< Toggle for debug drawing
	SFMLDebugDraw m_debugDraw; //!< Box2D debug drawing

	// Misc
	RectangleShape clickedPointRect;
	b2Vec2 playerMoveDirection;

public:
	Game(); //!< Constructor which sets up the game
	~Game(); //!< Destructor which cleans all the pointer memory up
	void update(float timestep); //!< Update the game with given timestep
	void draw(sf::RenderTarget& target, sf::RenderStates states) const; //!< Draw the game to the render context
	void toggleDebug() { m_debug = !m_debug; } //!< Toggle for debug drawing

	void processPlayerMovement();
	void processKeyboardInput(Keyboard::Key key, bool pressed); // pressed = true when pressed; false when released
	void processMouseScroll(Event::MouseWheelScrollEvent scrollEvent);
	void processMousePress(Event::MouseButtonEvent mouseButtonEvent, Vector2f& viewPos);
};