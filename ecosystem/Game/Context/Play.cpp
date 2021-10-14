#include "stdafx.h"
#include "Play.h"

Play::Play(sf::Vector2f windowSize) {
	m_grid = new Grid(sf::Vector2f(0, 0), windowSize, 10, 11);
}

Play::~Play() {
	delete m_grid;
}

void Play::update(float deltaTime) {

}

void Play::render(sf::RenderTarget& target) {
	target.clear(sf::Color(10, 150, 80));

	m_grid->render(target);
}

void Play::renderDebugMenu(sf::RenderTarget& target) {

}

void Play::handleEvent(sf::Event event) {

}

const char* Play::getContext() {
	return "dd";
}
