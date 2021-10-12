#pragma once

#include "../../Engine/Context/Context.h"

class Play : public Context {

public :
	Play();
	~Play();

	void update(float deltaTime) override;
	void render(sf::RenderTarget& target) override;
	void renderDebugMenu(sf::RenderTarget& target) override;
	void handleEvent(sf::Event event) override;
};