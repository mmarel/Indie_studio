#include "Game/Game.hpp"

void indie::Game::splashScreen() {
  _gameState = indie::GameState::MAIN_MENU;
  _gui.loadComponents(_gameState);
}

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
        tileType = tile.getType(0);
        if (tileHandlers.find(tileType) != tileHandlers.end()) { tileHandlers[tileType](x, y); }
      }
    }
  }
}
void indie::Game::process() {
  // main part
  static std::map<indie::GameState, indie::TurnHandler> handlers = {
    { indie::GameState::SPLASH_SCREEN, [this]() -> void { this->splashScreen(); } },
    { indie::GameState::INGAME, [this]() -> void { this->gameProcess(); } }
  };

  if (_gameState == indie::GameState::SPLASH_SCREEN) { return splashScreen(); }
  handleEvents();
  if (_gameState == indie::GameState::INGAME) { gameProcess(); }
}
