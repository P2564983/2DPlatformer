#include "DebugGrid.h"

void DebugGrid::updateGrid(View& view)
{
	if (m_autoGridSize)
	{
		m_gridSize = (Vector2i)view.getSize();
		if (m_gridSize.x % 2 == 0) m_gridSize.x -= 1;
		if (m_gridSize.y % 2 == 0) m_gridSize.y -= 1;
	}

	m_gridPoints = (m_gridSize.x + m_gridSize.y) * 2;
	m_offset = view.getCenter();
	m_grid.resize(m_gridPoints);
	if (m_gridPoints == 0) return; // no point continuing

	int i = 0;
	Vector2f limits = 0.5f * (Vector2f)(m_gridSize - Vector2i(1, 1));
	Vector2f mins = m_offset - limits;
	Vector2f maxs = m_offset + limits;

	// Vertical Lines: |
	for (float x = mins.x; i < m_gridSize.x * 2; i += 2, x++)
	{
		m_grid[i].position = Vector2f(x, mins.y - 1);
		m_grid[i + 1].position = Vector2f(x, maxs.y + 1);
		m_grid[i].color = m_grid[i + 1].color = m_colour;
	}
	// Horizontal Lines: -
	for (float y = mins.y; i < m_gridPoints; i += 2, y++)
	{
		m_grid[i].position = Vector2f(mins.x - 1, y);
		m_grid[i + 1].position = Vector2f(maxs.x + 1, y);
		m_grid[i].color = m_grid[i + 1].color = m_colour;
	}
}

DebugGrid::DebugGrid(View& view, bool autoGridSize, Vector2i gridSize, Color colour)
	: m_colour(colour), m_autoGridSize(autoGridSize), m_gridSize(gridSize)
{
	m_grid = VertexArray(Lines, 0);
	updateGrid(view);
}

void DebugGrid::setGridSize(const Vector2i gridSize)
{
	m_gridSize = gridSize;
}

void DebugGrid::setGridSize(const int width, const int height)
{
	m_gridSize.x = width;
	m_gridSize.y = height;
}

void DebugGrid::update(View& view)
{
	static Vector2f prevSize = view.getSize();

	if (view.getCenter() != m_offset || view.getSize() != prevSize)
	{
		prevSize = view.getSize();
		updateGrid(view);
	}
}

void DebugGrid::draw(RenderTarget& target, RenderStates states) const
{
	target.draw(m_grid);
}