#pragma once

/*!
\file Game.h
*/

#include "World.h"
#include "Player.h"
#include "ContactListener.h"
#include "DebugGrid.h"
#include "WorldGenerator.h"
#include "SFMLDebugDraw.h"
#include "TextureManager.h"
#include "UserInterface.h"

/*! \class Game
\brief Holds all information about the game, blocks, balls etc and allows updating and rendering.
*/

class Game : public Drawable
{
private:
	Vector2f m_worldSize = Vector2f(16.0f, 12.0f); //!< Size of the physical world in meters
	View m_view; //!< The view used for rendering (maps physical co-ordinates ^ to rendering (SFML) co-ordinates)

	// Box2D:
	b2World* m_pWorld = nullptr; //!< Pointer to the Box2D world. Using pointers as BOX2D has it's own memory management.
	const int mk_iVelIterations = 7; //!< On each update there will be 7 velocity iterations in the physics engine
	const int mk_iPosIterations = 5; //!< On each update there will be 5 position iterations
	const b2Vec2 mk_gravity = b2Vec2(0.f, 9.81f); //!< Standard earth gravity will be used (+ is down, - is up)

	// Objects within the world
	sf::RectangleShape m_background; //!< Background of the world
	Player* m_player; //!< The controllable actor in the world

	// Texture Manager and UI
	TextureManager textures;		//!< Manages all textures
	UserInterface* m_userInterface; //!< Draws a user interface

	// Other properties
	ContactListener m_contactListener; //!< A contact listener for all collisions
	WorldGenerator* m_worldGenerator; //!< The class object that continuosly generates and cleans up the world

	// Debugging
	SFMLDebugDraw m_debugDraw; //!< Box2D debug drawing
	bool m_debug = false; //!< Toggle for debug drawing
	DebugGrid* m_debugGrid;	//!< A grid drawn on top of the world
	bool m_debugGridDraw = false; //!< Toggle for debug grid drawing

	// Misc
	bool allowCameraZoom = false; // enable to allow scrolling to see World Generator in action

public:
	/*!
	  \brief Default Constructor used to setup the game
	*/
	Game();

	/*!
	  \brief Destructor which cleans all the pointer memory up
	*/
	~Game();

	/*!
	  \brief Update the game with given timestep 
	  \param timestep the timestep to update the physics world by
	*/
	void update(float timestep);

	/*!
	  \brief Draw the game to the render context
	  \param target the target to draw to (usually the window)
	  \param states the states used for drawing to a RenderTarget
	*/
	void draw(RenderTarget& target, RenderStates states) const;

	/*!
	  \brief Processes user keyboard input
	  \param key the physical key pressed/released
	  \param pressed flag indicating whether the key was pressed (true) or released (false)
	*/
	void processKeyboardInput(Keyboard::Key key, bool pressed);

	/*!
	  \brief Processes user mouse scroll only if allowCameraZoom is true
	  \param scrollEvent the SFML MouseWheelScrollEvent containing information about mouse scroll
	*/
	void processMouseScroll(Event::MouseWheelScrollEvent scrollEvent);

	/*!
	  \brief Processes user mouse click
	  \param mouseButtonEvent the SFML MouseButtonEvent containing information about the mouse click
	  \param viewPos where in the view the mouse was clicked
	*/
	void processMousePress(Event::MouseButtonEvent mouseButtonEvent, Vector2f& viewPos);
};