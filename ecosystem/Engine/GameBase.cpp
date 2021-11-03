#include "stdafx.h"
#include <Engine/GameBase.h>
#include <iostream>

static constexpr float APP_MAX_FRAMERATE{ 60.0f };

static const sf::Vector2u APP_INIT_WINDOW_SIZE{ 1024, 768 };

GameBase::GameBase(const char* title) : 
    m_window
    { 
        sf::VideoMode(APP_INIT_WINDOW_SIZE.x, APP_INIT_WINDOW_SIZE.y), 
        title, 
        sf::Style::Titlebar | sf::Style::Close 
    }
{
    m_window.setVerticalSyncEnabled(true);
    m_window.setFramerateLimit(static_cast<uint32_t>(APP_MAX_FRAMERATE));
    m_window.setActive();
}

GameBase::~GameBase(){
}

void GameBase::RunGameLoop(){

    float deltaTime{ 1.0f / APP_MAX_FRAMERATE };
    sf::Clock clock;

    while (m_window.isOpen())
    {
        clock.restart();
        sf::Event event;
       
        if (m_window.pollEvent(event)) 
        {
            switch (event.type) 
            {
                case sf::Event::Closed:
                    m_window.close();
                    break;

                case sf::Event::KeyPressed:  
                    if (event.key.code == sf::Keyboard::Escape) {  m_window.close(); }
                    break;
            }
            HandleEvent(event);
        }

        sf::sleep(sf::milliseconds(50));

        Update(deltaTime);
        Render(m_window); 
        RenderDebugMenu(m_window);

        m_window.display();

        deltaTime = clock.getElapsedTime().asSeconds();
    }
 
}

sf::Vector2f GameBase::getWindowSize() {
    return sf::Vector2f(m_window.getSize().x, m_window.getSize().y);
}
