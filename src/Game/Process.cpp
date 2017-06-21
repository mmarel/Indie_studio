#include "Game/Game.hpp"

void indie::Game::AIhandler() {
  std::map<AiAction, std::function<void(size_t)> > actionHandlers = {
    { AiAction::AI_UP, [this](size_t playerId) { this->move(playerId, ELookAt::NORTH); }},
    { AiAction::AI_DOWN, [this](size_t playerId) { this->move(playerId, ELookAt::SOUTH); }},
    { AiAction::AI_LEFT, [this](size_t playerId) { this->move(playerId, ELookAt::WEST); }},
    { AiAction::AI_RIGHT, [this](size_t playerId) { this->move(playerId, ELookAt::EAST); }},
    { AiAction::AI_BOMB, [this](size_t playerId) { this->bomb(playerId); }}
  };
  std::for_each(_players.begin(), _players.end(),
    [&](std::unique_ptr<Player> &player) {
      if (player->getType() == indie::PlayerType::PLAYER_AI && player->isAlive())
        {
          AiAction action = player->think();

          if (actionHandlers.find(action) != actionHandlers.end()) {
            actionHandlers[action](player->getId());
          }
        }
    });
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
  _gui.flushGUI();
  if (handlers.find(_gameState) != handlers.end()) { return handlers[_gameState](); }
  //handleEvents();
  gameProcess();
}
