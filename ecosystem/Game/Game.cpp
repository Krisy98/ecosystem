#include "stdafx.h"

#include "Game.h"
#include "Context/Menu.h"
#include "Context/Play.h"

Game::Game() :
    m_title{ "Ecosystem" },
    GameBase{m_title}
{
    menu();
}

void Game::Update(float deltaTime){
    m_context->update(deltaTime);
}

void Game::Render(sf::RenderTarget& target){
    target.clear();

    m_context->render(target);
}

void Game::RenderDebugMenu(sf::RenderTarget& target){

    m_context->renderDebugMenu(target);
}

void Game::HandleEvent(sf::Event event){
    m_context->handleEvent(event);

    std::string currentContext = m_context->getContext();

    if (currentContext != m_context_str) {

        if (currentContext == "start")
        {
            delete m_context;
            start();
        }

        
    }

    
}

void Game::menu() {
    m_context = new Menu(m_title, getWindowSize());
    m_context_str = "menu";
}

void Game::start() {
    m_context = new Play(getWindowSize());
    m_context_str = "start";
}
