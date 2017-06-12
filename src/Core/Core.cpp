//
// Author: Maud Marel
// Date: 2017-05-23 14:09:04
//

#include <iostream>
#include <chrono>
#include <thread>
#include <memory>
#include "Core/Core.hpp"

indie::Core::Core()
    : 
        _gfx(std::make_unique<indie::Gfx>()),
        _game(), // set make unique with the game when merge will be ok with game part
        _sounds(),
        _gameState(indie::GameState::NONE)
{

}

indie::Core::~Core()
{

}


void            indie::Core::runCoreLoop()
{

    while (42) {

      this->_gameState = this->_game->getGameState();

      this->_gfx->clear();

      switch(this->_gameState)
        {

          case indie::GameState::QUIT:
              return ;
              break ;

          case indie::GameState::LOADING:
              this->loading();
              break ;

          case indie::GameState::INGAME:
          case indie::GameState::MENU:
          case indie::GameState::SCORE:
          case indie::GameState::SETTINGS:
          case indie::GameState::ROOM:
              this->process();
              break ;

          case indie::GameState::NONE:
          case indie::GameState::SPLASH_SCREEN: // To change when splash will be ready.
          default:
              break ;

      }

  }
}
