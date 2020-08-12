#pragma once

/*!
\file DebugGrid.h
*/

#include <SFML/Graphics.hpp>
#include <iostream>

using namespace sf;
using namespace std;

/*! \class DebugGrid
\brief A drawable grid used for debugging purposes
*/
class DebugGrid : public Drawable
{
private:
	Color m_colour; //!< The grid colour
	VertexArray m_grid;	//!< The points that make up the grid
	Vector2i m_gridSize; //!< The grid's dimensions
	int m_gridPoints; //!< The number of grid points
	Vector2f m_offset; //!< An offset used when setting up and drawing the grid

	/*!
	  \brief Updates the grids size and position depending on the view
	  \param view the view used to base the updates on - this is usually the view used to render the game world
	*/
	void updateGrid(View& view);

public:
	/*!
	  \brief Constructor to setup a debig grid
	  \param view the view the debug grid is rendered to
	  \param autoGridSize flag determining whether the grid size should be the same as the view size
	  \param gridSize the size of the gird - this value is overeidden if autoGridSize is set to true
	  \param colour the grid colour
	*/
	DebugGrid(View& view, bool autoGridSize = true, const Vector2i gridSize = Vector2i(0, 0), Color colour = Color::Magenta);

	/*!
	  \brief Set the grid size - this method disables autoGridSize;
	  /param gridSize the new grid size
	*/
	void setGridSize(const Vector2i gridSize);

	/*!
	  \brief Set the grid size - this method disables autoGridSize;
	  /param width the width of the new grid
	  \param height the height of the new grid
	*/
	void setGridSize(const int width, const int height);

	/*!
	  \brief Updates the grids position (and size if autoGridSize is true)
	  \param view the view used to base the updates on - this is usually the view used to render the game world
	*/
	void update(View& view);

	/*!
	  \brief Draw the grid to render context
	  \param target the target to draw to (usually the window)
	  \param states the states used for drawing to a RenderTarget
	*/
	void draw(RenderTarget& target, RenderStates states) const;

	bool m_autoGridSize; //!< Flag determining whether the grid size and view size should be the same
};