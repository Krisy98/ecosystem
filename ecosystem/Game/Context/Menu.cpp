#include "stdafx.h"

#include "Menu.h"

#include <string>
#include <cstring>

Menu::Menu(const char* gameTitle, sf::Vector2f windowSize){
	m_context = "menu";
	const char* strings[2] = {"start", "synopsis"};
	sf::Vector2f position(windowSize.x/2, windowSize.y/6);

	m_gameTitle = new Text(gameTitle, sf::Color(255, 255, 255), position, 45);

	position.y += windowSize.y / 6;

	for (int i = 0; i < 2; i++) 
	{
		m_options[i] = new Text(strings[i], sf::Color(220, 220, 220), position);

		position.y += windowSize.y / 12;
	}
}

Menu::~Menu() {
	delete m_gameTitle;
}

void Menu::update(float deltaTime){


}

void Menu::render(sf::RenderTarget& target) {
	if (m_gameTitle->isOperational()) { target.draw(m_gameTitle->getText()); }

	for (int i = 0; i < 2; i++) {
		if (m_options[i]->isOperational()) target.draw(m_options[i]->getText());
	}
}

void Menu::renderDebugMenu(sf::RenderTarget& target) {

}

void Menu::handleEvent(sf::Event event) {
	sf::Vector2f mouseMove(event.mouseMove.x, event.mouseMove.y);
	sf::Vector2f mouseButton(event.mouseButton.x, event.mouseButton.y);

	bool treated = false;

	switch (event.type)
	{
		case sf::Event::MouseMoved:

			for (int i = 0; i < size; i++) {
				if (m_options[i]->getText().getGlobalBounds().contains(mouseMove)) {

					float optionWidth = m_options[i]->getText().getGlobalBounds().width;

					treated = true;

					m_options[i]->setColor(sf::Color(0, 200, 50));
				}
			}

			if (!treated)
			{
				for (int i = 0; i < size; i++)
				{
					m_options[i]->setColor(sf::Color(220, 220, 220));
				}
			}
			break;

		case sf::Event::MouseButtonReleased:

			for (int i = 0; i < size; i++) {
				if (m_options[i]->getText().getGlobalBounds().contains(mouseButton) && m_options[i]->getText().getString().getSize() > 0) {

					m_context = m_options[i]->getText().getString().toAnsiString();
				}
			}
			break;
		
	}

}

const char* Menu::getContext() {
	return m_context.c_str();
}

