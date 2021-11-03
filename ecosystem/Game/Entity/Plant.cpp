#include "stdafx.h"
#include "Plant.h"

#include <iostream>

Plant::Plant(sf::Vector2i indexesPosition, sf::Vector2f size) :
	m_expansionTime{
		sf::seconds(20.f)
	}
{

	sf::Vector2f position(indexesPosition.x * size.x, indexesPosition.y * size.y);

	setPosition(position);
	setSize(size);
	setSpeed(sf::Vector2f(0.0f, 0.0f));

	this->indexesPos = indexesPosition;

	if (!m_plantTexture.loadFromFile(".\\Assets\\sprite_sheet/flower.png")) {
		std::cout << "error loading file texture ..." << std::endl;
	}

	m_skin.setTexture(m_plantTexture);
	m_skin.setTextureRect(sf::IntRect(0, 0, 200, 200));
	m_skin.setPosition(position);


	m_skin.setScale(size.x / 200, size.y / 200);

	m_clock.restart();
}

Plant::~Plant() {
}

void Plant::update(float deltaTime) {

}

void Plant::render(sf::RenderTarget& target) {
	target.draw(m_skin);
}

void Plant::handleEvent(sf::Event event) {

}

sf::Vector2i Plant::getIndexes() {
    return indexesPos;
}

bool Plant::pollination() {
	if (m_clock.getElapsedTime().asSeconds() >= m_expansionTime.asSeconds())
	{
		m_clock.restart();
		return true;
	}
	return false;
}
