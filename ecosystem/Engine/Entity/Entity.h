#pragma once

#include "../Physics/Collision.h"

class Entity : public BoxCollideable {

public :

	virtual void update(float deltaTime) = 0;
	virtual void render(sf::RenderTarget& target) = 0;
	virtual void handleEvent(sf::Event event) = 0;

	void setPosition(sf::Vector2f position);
	void setSize(sf::Vector2f size);
	void setSpeed(sf::Vector2f speed);

	sf::Vector2f getPosition();
	sf::Vector2f getSize();
	sf::Vector2f getSpeed();

private:
	sf::Vector2f m_position{};
	sf::Vector2f m_size{};
	sf::Vector2f m_speed{};
};