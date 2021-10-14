#include "stdafx.h"
#include "Arrow.h"

Arrow::Arrow(sf::Vector2f size, sf::Vector2f position, sf::Color color) {

	float base_width = size.x / 3;

	m_arrow.setPointCount(7);

	m_arrow.setPoint(0, sf::Vector2f(size.x / 2, 0));
	m_arrow.setPoint(1, sf::Vector2f(size.x, size.y/2));
	m_arrow.setPoint(2, sf::Vector2f(size.x - base_width, size.y / 2));
	m_arrow.setPoint(3, sf::Vector2f(size.x - base_width, size.y));
	m_arrow.setPoint(4, sf::Vector2f(base_width, size.y));
	m_arrow.setPoint(5, sf::Vector2f(base_width, size.y / 2));
	m_arrow.setPoint(6, sf::Vector2f(0, size.y / 2));

	m_arrow.setPosition(position);
	m_arrow.setFillColor(color);

}

Arrow::~Arrow() {

}

sf::ConvexShape Arrow::get() {
	return m_arrow;
}

void Arrow::setColor(sf::Color color) {
	m_arrow.setFillColor(color);
}

void Arrow::setRotation(float angle) {
	m_arrow.setRotation(angle);
}
