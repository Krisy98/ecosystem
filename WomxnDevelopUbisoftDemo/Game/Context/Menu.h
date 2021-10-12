#pragma once

#include "../../Engine/Context/Context.h"
#include "../../Engine/Graphics/Text.h"

class Menu : public Context {

public:

	Menu(const char* gameTitle, sf::Vector2f windowSize);
	~Menu();

	void update(float deltaTime) override;
	void render(sf::RenderTarget& target) override;
	void renderDebugMenu(sf::RenderTarget& target) override;
	void handleEvent(sf::Event event) override;

private:
	const char* gameTitle = {};
	Text* m_text = {};
};

