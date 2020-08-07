#pragma once

/*!
\file DebugGrid.h
*/

#include <SFML/Graphics.hpp>
#include <iostream>

using namespace sf;
using namespace std;

class DebugGrid : public Drawable
{
private:
	Color m_colour;
	VertexArray m_grid;
	Vector2i m_gridSize;
	int m_gridPoints;
	Vector2f m_offset;

	void updateGrid(View& view);

public:
	DebugGrid(View& view, bool autoGridSize = true, const Vector2i gridSize = Vector2i(0, 0), Color colour = Color::Magenta);
	void setGridSize(const Vector2i gridSize);
	void setGridSize(const int width, const int height);
	void update(View& view);
	void draw(RenderTarget& target, RenderStates states) const;
	bool m_autoGridSize;
};