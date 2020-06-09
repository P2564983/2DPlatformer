/**
@file scene.cpp
*/

#include "scene.h"

Scene::Scene()
{
	// Textures
	textures.addTexture("square", "assets//textures//square.png");
	textures.addTexture("rect", "assets//textures//rect.png");


	// Shapes
	RectangleShape rect(Vector2f(800, 600));
	rect.setFillColor(Color(225, 225, 225));
	rects.push_back(rect);

	rect.setSize(Vector2f(50, 50));
	rect.setPosition(375, 275);
	rect.setTexture(textures.getTexture("square"));
	rects.push_back(rect);

	rect.setSize(Vector2f(50, 100));
	rect.setPosition(325, 250);
	rect.setTexture(textures.getTexture("rect"));
	rects.push_back(rect);

	rect.setPosition(425, 250);
	rects.push_back(rect);

	// Views
	// Main View
	mainView.setCenter(Vector2f(400, 300));
	mainView.setSize(Vector2f(200, 150));
	// Mini View
	miniView.setCenter(Vector2f(400, 300));
	miniView.setSize(Vector2f(800, 600));
	miniView.setViewport(FloatRect(0.85f, 0.85f, 0.15f, 0.15f));
}

void Scene::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	// First draw the Main View
	target.setView(mainView);
	for (int i = 1; i < rects.size(); ++i)
		target.draw(rects[i]);

	// Then draw the Mini View
	target.setView(miniView);
	for (auto it = rects.begin(); it != rects.end(); ++it)
		target.draw(*it);
}
