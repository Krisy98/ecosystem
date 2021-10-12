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
    target.clear(sf::Color(0, 0, 0));

    m_context->render(target);
}

void Game::RenderDebugMenu(sf::RenderTarget& target){

    m_context->renderDebugMenu(target);
}

void Game::HandleEvent(sf::Event event){
    m_context->handleEvent(event);
}

void Game::menu() {
    m_context = new Menu(m_title, getWindowSize());
}
