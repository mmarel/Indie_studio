#include "Game/Game.hpp"

indie::Game::Game() :
  _sounds(),
  _gameState(SPLASH_SCREEN),
  _events(),
  _map(0),
  _gui(),
  _settings({ 50, IA_LEVEL::IA_MEDIUM, std::vector<Player>(), 1}),
  _objectsStates()
 {}

indie::Game::~Game() {}

indie::GameState indie::Game::getGameState() const {
  return _gameState;
}

void indie::Game::notifyEvent(std::vector<Event> &&events) {
  _events.insert(_events.end(), events.begin(), events.end());
}

const std::vector<size_t> &indie::Game::getObjectsId() const {
  return _map.getObjectsId();
}

const std::vector<indie::Sound> &indie::Game::getSoundsToPlay() const {
  return _sounds;
}

const indie::IMap &indie::Game::getCurrentMap() const {
  return _map;
}

const indie::IGUI &indie::Game::getCurrentGUI() const {
  return _gui;
}

void indie::Game::setObjectsAnimationState(const std::vector<indie::AnimationState> &objectsStates) {
  _objectsStates = objectsStates;
}
