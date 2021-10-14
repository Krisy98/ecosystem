#pragma once

#include <vector>

class Grid {

public:
	Grid(sf::Vector2f coords, sf::Vector2f size, int nRows, int nColmuns);
	~Grid();

	void render(sf::RenderTarget& target);

	int getNRows();
	int getNColumns();

private:
	sf::Vector2f m_coords;
	sf::Vector2f m_size;

	std::vector<sf::RectangleShape> m_lines;

	int m_nRows;
	int m_nColumns;

	void build();
};

