#pragma once

#include "../../Engine/Context/Context.h"
#include "../../Engine/Graphics/Grid.h"

class Play : public Context {

public :
	Play(sf::Vector2f windowSize);
	~Play();

	void update(float deltaTime) override;
	void render(sf::RenderTarget& target) override;
	void renderDebugMenu(sf::RenderTarget& target) override;
	void handleEvent(sf::Event event) override;

	const char* getContext() override;
	
private:
	Grid* m_grid;
};