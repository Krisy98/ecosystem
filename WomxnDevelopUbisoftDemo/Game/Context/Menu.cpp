#include "stdafx.h"

#include "Menu.h"

Menu::Menu(const char* gameTitle, sf::Vector2f windowSize) {

	sf::Vector2f position(windowSize.x/2, windowSize.y/4);

	this->gameTitle = gameTitle;
	m_text = new Text(gameTitle, sf::Color(255, 255, 255), position, 45);
}

Menu::~Menu() {
	delete m_text;
}

void Menu::update(float deltaTime){

	

}

void Menu::render(sf::RenderTarget& target) {
	if (m_text->isOperational())
	{
		target.draw(m_text->getText());
	}
}

void Menu::renderDebugMenu(sf::RenderTarget& target) {

}

void Menu::handleEvent(sf::Event event) {

}
