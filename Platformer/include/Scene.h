#pragma once

/**
@file scene.h
*/

#include <vector>
#include <SFML/Graphics.hpp>
#include "TextureManager.h"

using namespace std;
using namespace sf;

class Scene : public sf::Drawable //!< \Class Scene class draw a basic scene
{
private:
	TextureManager textures;		//!< Manages all textures
	vector<RectangleShape> rects;	//!< Shapes to be drawn

	View mainView; //!< Main View used in the scene
	View miniView; //!< Mini View used in the scene

public:
	Scene(); //!< Constructor the sets up the scene
	void draw(sf::RenderTarget& target, sf::RenderStates states) const override; //!< Overidden draw function from drawable - does the drawing
};