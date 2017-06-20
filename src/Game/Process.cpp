#include "Game/Game.hpp"

void indie::Game::AIhandler() {
}

void indie::Game::splashScreen() {
  _gameState = indie::GameState::MAIN_MENU;
  _gui.loadComponents(_gameState);
}

void indie::Game::gameProcess() {
  updateAnimations();
  handleEvents();
  AIhandler();
}

void indie::Game::menuProcess() {
  indie::Timer  timer;

  handleEvents();
  while (timer.Elapsed().count() < 70);
}

void indie::Game::process() {
  static std::map<indie::GameState, indie::TurnHandler> handlers = {
    { indie::GameState::SPLASH_SCREEN, [this]() -> void { this->splashScreen(); } },
    { indie::GameState::INGAME, [this]() -> void { this->gameProcess(); } },
    { indie::GameState::MAIN_MENU, [this]() -> void { this->menuProcess(); } },
    { indie::GameState::SETTINGS, [this]() -> void { this->menuProcess(); } },
    { indie::GameState::ROOM, [this]() -> void { this->menuProcess(); } },
    { indie::GameState::SCOREBOARD, [this]() -> void { this->menuProcess(); } }
  };
  
  _soundsToPlay.clear();
  if (handlers.find(_gameState) != handlers.end()) { return handlers[_gameState](); }
  handleEvents();
}
