#include "Game/Game.hpp"

void indie::Game::move_left(indie::Player &player) {
  double newShift;
  indie::Tile playerTile = _map.at(0, player.x, player.y);

  playerTile.setObjectRotation(indie::ELookAt::WEST);
  newShift = playerTile.getShiftX() - PLAYER_SPEED;
  playerTile.setShiftX(newShift);
}

void indie::Game::move_right(indie::Player &player) {
  double newShift;
  indie::Tile playerTile = _map.at(0, player.x, player.y);

  playerTile.setObjectRotation(indie::ELookAt::EAST);
  newShift = playerTile.getShiftX() + PLAYER_SPEED;
  playerTile.setShiftX(newShift);
}

void indie::Game::move_down(indie::Player &player) {
  double newShift;
  indie::Tile playerTile = _map.at(0, player.x, player.y);

  playerTile.setObjectRotation(indie::ELookAt::SOUTH);
  newShift = playerTile.getShiftY() + PLAYER_SPEED;
  playerTile.setShiftY(newShift);
}

void indie::Game::move_up(indie::Player &player) {
  double newShift;
  indie::Tile playerTile = _map.at(0, player.x, player.y);

  playerTile.setObjectRotation(indie::ELookAt::NORTH);
  newShift = playerTile.getShiftY() - PLAYER_SPEED;
  playerTile.setShiftY(newShift);
}

void indie::Game::bomb(indie::Player &player) {
  indie::Tile playerTile = _map.at(0, player.x, player.y);
}

void indie::Game::handleEvents() {

  std::remove_if(_events.begin(), _events.end(),
  [this](Event &event)-> bool{
    std::vector<indie::Player>::iterator it;

    if (_gameState == indie::GameState::INGAME &&
        event.type == indie::EventType::ET_KEYBOARD &&
        event.action == indie::ActionType::AT_PRESSED) {
        if ((it = std::find_if(_settings.players.begin(), _settings.players.end(),
                  [&event](Player &psettings)-> bool{
                    return event.kb_key == psettings.move_left;
                  })) != _settings.players.end()) { move_left(*it); }
        else if ((it = std::find_if(_settings.players.begin(), _settings.players.end(),
                        [&event](Player &psettings)-> bool{
                          return event.kb_key == psettings.move_right;
                        })) != _settings.players.end()) { move_right(*it); }
        else if ((it = std::find_if(_settings.players.begin(), _settings.players.end(),
                        [&event](Player &psettings)-> bool{
                          return event.kb_key == psettings.move_down;
                        })) != _settings.players.end()) { move_down(*it); }
        else if ((it = std::find_if(_settings.players.begin(), _settings.players.end(),
                        [&event](Player &psettings)-> bool{
                          return event.kb_key == psettings.move_up;
                        })) != _settings.players.end()) { move_up(*it); }
        else if ((it = std::find_if(_settings.players.begin(), _settings.players.end(),
                        [&event](Player &psettings)-> bool{
                          return event.kb_key == psettings.bomb;
                        })) != _settings.players.end()) { bomb(*it); }

      } else if (_gameState == indie::GameState::MENU ||
                _gameState == indie::GameState::SETTINGS ||
                _gameState == indie::GameState::SCORE ||
                _gameState == indie::GameState::ROOM) {
        // call keymap
      }
    return true;
  });
}
