#pragma once

#include <cstdio>
#include <iostream>

class Text {

public:
	Text(const char* string, sf::Color color,  sf::Vector2f position);
	Text(const char* string, sf::Color color, sf::Vector2f position, int size);
	~Text();

	sf::Text getText();
	bool isOperational();

private :
	sf::Text m_text;
	sf::Font m_font;
	const char* m_string;
	int m_characterSize;
	sf::Color m_color;
	sf::Vector2f m_position = {};
	bool m_operational = false;

	void init();
};