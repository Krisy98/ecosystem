#include "stdafx.h"
#include "Text.h"

Text::Text(const char* string, sf::Color color, sf::Vector2f position) :
	m_characterSize{ 24 }
{
	m_string = string;
	m_color = color;
	m_position = position;

	init();
}

Text::Text(const char* string, sf::Color color, sf::Vector2f position, int characterSize) {
	m_string = string;
	m_color = color;
	m_characterSize = characterSize;
	m_position = position;

	init();
}

Text::~Text() {

}

sf::Text Text::getText() {
	return m_text;
}

void Text::setColor(sf::Color color) {
	m_text.setFillColor(color);
}

bool Text::isOperational() {
	return m_operational;
}

void Text::init() {

	if (m_font.loadFromFile("Assets\\font/arial.ttf"))
	{
		m_operational = true;
	}

	m_text.setFont(m_font);
	m_text.setString(m_string);
	m_text.setCharacterSize(m_characterSize);
	m_text.setFillColor(m_color);
	m_text.setPosition(m_position);
	
	m_position.x -= m_text.getGlobalBounds().width / 2;
	m_position.y -= m_text.getGlobalBounds().height / 2;

	m_text.setPosition(m_position);
}
