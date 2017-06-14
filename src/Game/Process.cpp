#include "Game/Game.hpp"

void indie::Game::splashScreen() {
  static int duration = 0;

  duration++;
  if (duration == 20) {
    _gameState = indie::GameState::MENU;
  }
}

void indie::Game::menuProcess() {}

void indie::Game::gameProcess() {
  static std::map<indie::OBJECTS_ID, indie::TileHandler> tileHandlers = {
    { indie::OBJECTS_ID::PLAYER_ONE,
      [this](const std::size_t &px, const std::size_t &py) -> void { this->handlePlayer(px, py, 1); }},
    { indie::OBJECTS_ID::SQUAREBOMB,
      [this](const std::size_t &px, const std::size_t &py) -> void { this->handleBomb(px, py); }}
  };
  std::size_t width = _map.getWidth();
  std::size_t height = _map.getHeight();
  Tile tile;
  indie::OBJECTS_ID tileType = indie::OBJECTS_ID::EMPTY;

  for (std::size_t layer = 0; layer < 2; layer++) {
    for (std::size_t y = 0; y < height; y++) {
      for (std::size_t x = 0; x < width; x++) {
        tile = _map.at(layer, x, y);
        tileType = tile.getType();
        if (tileHandlers.find(tileType) != tileHandlers.end()) { tileHandlers[tileType](x, y); }
      }
    }
  }
}
void indie::Game::quit() {}

void indie::Game::process() {
  // main part
  static std::map<indie::GameState, indie::TurnHandler> handlers = {
    { indie::GameState::SPLASH_SCREEN, [this]() -> void { this->splashScreen(); } },
    { indie::GameState::MENU, [this]() -> void { this->menuProcess(); } },
    { indie::GameState::INGAME, [this]() -> void { this->gameProcess(); } },
    { indie::GameState::QUIT, [this]() -> void { this->quit(); } }
  };

  handleEvents();
  _gui.loadComponents(_gameState);
  if (handlers.find(_gameState) != handlers.end()) { handlers[_gameState](); }
}
