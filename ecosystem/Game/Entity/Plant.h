#pragma once

#include "../../Engine/Entity/Entity.h"

class Plant : public Entity {

public :
	Plant(sf::Vector2i indexesPosition, sf::Vector2f size);
	~Plant();

	void update(float deltaTime) override;
	void render(sf::RenderTarget& target) override;
	void handleEvent(sf::Event event) override;

	sf::Vector2i getIndexes();

	bool pollination();

private:
	sf::Clock m_clock;
	sf::Time m_expansionTime;

	sf::Vector2i indexesPos;

	sf::Sprite m_skin;
	sf::Texture m_plantTexture;

};

