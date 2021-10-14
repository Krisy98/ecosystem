#pragma once

class Arrow {

public :
	Arrow(sf::Vector2f size, sf::Vector2f position, sf::Color color);
	~Arrow();

	sf::ConvexShape get();

	void setColor(sf::Color color);
	void setRotation(float angle);
	

private:
	sf::ConvexShape m_arrow;
};

