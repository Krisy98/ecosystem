#include "stdafx.h"
#include "Entity.h"

void Entity::setPosition(sf::Vector2f position) {
	m_position = position;
}

void Entity::setSize(sf::Vector2f size) {
	m_size = size;
}

void Entity::setSpeed(sf::Vector2f speed) {
	m_speed = speed;
}

sf::Vector2f Entity::getPosition() {
	return m_position;
}

sf::Vector2f Entity::getSize() {
	return m_size;
}

sf::Vector2f Entity::getSpeed() {
	return m_speed;
}
