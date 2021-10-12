#pragma once

class GameBase {

public:
    GameBase(const char* title);
    virtual ~GameBase();

    void RunGameLoop();

protected:

    virtual void Update(float deltaTime) = 0;
    virtual void Render(sf::RenderTarget& target) = 0;
    virtual void RenderDebugMenu(sf::RenderTarget& target) = 0;
    virtual void HandleEvent(sf::Event event) = 0;

    sf::Vector2f getWindowSize();

private:
    sf::RenderWindow m_window;
};