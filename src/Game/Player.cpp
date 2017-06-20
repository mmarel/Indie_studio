#include "Game/Player.hpp"

indie::Player::Player(size_t id) :
  _id(id),
  _bindings(),
  _bombType(indie::OBJECTS_ID::PIKESBOMB),
  _bombs(),
  _score(0),
  _alive(true) {
    if (id == 1) {
    _bindings = {
      { "LEFT", indie::KeyboardKey::KB_Q },
      { "RIGHT", indie::KeyboardKey::KB_D },
      { "DOWN", indie::KeyboardKey::KB_S },
      { "UP", indie::KeyboardKey::KB_Z },
      { "BOMB", indie::KeyboardKey::KB_E }
    }; }
    else if (id == 2) {
      _bombType = indie::OBJECTS_ID::SQUAREBOMB;
      _bindings = {
        { "LEFT", indie::KeyboardKey::KB_ARROW_LEFT },
        { "RIGHT", indie::KeyboardKey::KB_ARROW_RIGHT},
        { "DOWN", indie::KeyboardKey::KB_ARROW_DOWN },
        { "UP", indie::KeyboardKey::KB_ARROW_UP },
        { "BOMB", indie::KeyboardKey::KB_ENTER }
      };
    }
}

bool indie::Player::hasBomb(size_t id) const {
  return std::find_if(_bombs.begin(), _bombs.end(),
          [&id](const size_t &idSaved) {
            return id == idSaved;
          }) != _bombs.end();
}

void indie::Player::removeBomb(size_t id) {
  std::remove(_bombs.begin(), _bombs.end(), id);
}
