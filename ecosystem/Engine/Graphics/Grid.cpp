#include "stdafx.h"
#include "Grid.h"

Grid::Grid(sf::Vector2f coords, sf::Vector2f size, int nRows, int nColumns) {
	m_coords = coords;
	m_size = size;
	
	m_nRows = nRows;
	m_nColumns = nColumns;

	build();
}

Grid::~Grid() {
}

void Grid::render(sf::RenderTarget& target) {

	for (int i = 0; i < m_lines.size(); i++)
	{
		target.draw(m_lines.at(i));
	}

}

int Grid::getNRows() {
	return m_nRows;
}

int Grid::getNColumns() {
	return m_nColumns;
}

void Grid::build() {
	float base = m_size.x / m_nColumns;

	for (int i = 0; i < m_nColumns-1; i++)
	{
		sf::RectangleShape line;

		line.setPosition(sf::Vector2f(base*(i + 1), 0));
		line.setFillColor(sf::Color(100, 100, 100));
		line.setSize(sf::Vector2f(1, m_size.y));

		m_lines.push_back(line);
	}

	base = m_size.y / m_nRows;

	for (int i = 0; i < m_nRows - 1; i++)
	{
		sf::RectangleShape line;

		line.setPosition(sf::Vector2f(0, base*(i + 1)));
		line.setFillColor(sf::Color(100, 100, 100));
		line.setSize(sf::Vector2f(m_size.x, 1));

		m_lines.push_back(line);
	}

}
