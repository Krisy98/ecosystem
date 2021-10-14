#pragma once

#include <iostream>

#include "../../Engine/Context/Context.h"
#include "../../Engine/Graphics/Text.h"
#include "../../Engine/Graphics/Arrow.h"

class Menu : public Context {

public:

	Menu(const char* gameTitle, sf::Vector2f windowSize);
	~Menu();

	void update(float deltaTime) override;
	void render(sf::RenderTarget& target) override;
	void renderDebugMenu(sf::RenderTarget& target) override;
	void handleEvent(sf::Event event) override;

	const char* getContext() override;

private:
	Text* m_gameTitle = {};
	Text* m_options[2];
	int size = 2;
	std::string m_context;
};

