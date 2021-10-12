#pragma once

#include <Engine/GameBase.h>
#include "../Engine/Context/Context.h"

class Game : public GameBase{

public:
    Game();

    void Update(float deltaTime) override;
    void Render(sf::RenderTarget& target) override;
    void RenderDebugMenu(sf::RenderTarget& target) override;
    void HandleEvent(sf::Event event) override;

private:
    Context* m_context = {};
    const char* m_title;

    /// <summary>
    /// set the context as menu
    /// </summary>
    void menu();
};