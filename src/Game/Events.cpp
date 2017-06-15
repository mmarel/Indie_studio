#include "Game/Game.hpp"

void indie::Game::move_left(indie::Tile &player,
                            size_t x, size_t y) {
  double newShift;
  indie::Tile nearPlayerTile;
  indie::Tile nearBombTile;

  player.setObjectRotation(0, indie::ELookAt::WEST);
  newShift = player.getShiftX(0) - PLAYER_SPEED;
  player.setShiftX(0, newShift);

  if (newShift < 0.0 && x > 0) {
    nearPlayerTile = _map.at(0, x - 1, y);
    nearBombTile = _map.at(1, x - 1, y);

    // Players and Bombs are blocking movements
    if (nearPlayerTile.getType(0) == indie::OBJECTS_ID::EMPTY &&
        nearBombTile.getType(0) == indie::OBJECTS_ID::EMPTY) {
      nearPlayerTile = player;
      player.reset();
      nearPlayerTile.setShiftX(0, 1.0 + newShift);
    }
  } else if (newShift < 0.0 && x == 0) { player.setShiftX(0, 0.0); }
}

void indie::Game::move_right(indie::Tile &player,
                              size_t x, size_t y) {
  double newShift;
  indie::Tile nearPlayerTile;
  indie::Tile nearBombTile;

  player.setObjectRotation(0, indie::ELookAt::EAST);
  newShift = player.getShiftX(0) + PLAYER_SPEED;
  player.setShiftX(0, newShift);

  if (newShift > 1.0 && x < (_map.getWidth() - 1)) {
    nearPlayerTile = _map.at(0, x + 1, y);
    nearBombTile = _map.at(1, x + 1, y);

    // Players and Bombs are blocking movements
    if (nearPlayerTile.getType(0) == indie::OBJECTS_ID::EMPTY &&
        nearBombTile.getType(0) == indie::OBJECTS_ID::EMPTY) {
      nearPlayerTile = player;
      player.reset();
      nearPlayerTile.setShiftX(0, newShift - 1.0);
    }
  } else if (newShift > 1.0) { player.setShiftX(0, 1.0); }
}

void indie::Game::move_down(indie::Tile &player,
                            size_t x, size_t y) {
  double newShift;
  indie::Tile nearPlayerTile;
  indie::Tile nearBombTile;

  player.setObjectRotation(0, indie::ELookAt::SOUTH);
  newShift = player.getShiftY(0) + PLAYER_SPEED;
  player.setShiftY(0, newShift);

  if (newShift > 1.0 && y < (_map.getHeight() - 1)) {
    nearPlayerTile = _map.at(0, x, y + 1);
    nearBombTile = _map.at(1, x, y + 1);

    // Players and Bombs are blocking movements
    if (nearPlayerTile.getType(0) == indie::OBJECTS_ID::EMPTY &&
        nearBombTile.getType(0) == indie::OBJECTS_ID::EMPTY) {
      nearPlayerTile = player;
      player.reset();
      nearPlayerTile.setShiftY(0, newShift - 1.0);
    }
  } else if (newShift > 1.0) { player.setShiftY(0, 1.0); }

}

void indie::Game::move_up(indie::Tile &player,
                          size_t x, size_t y) {
  double newShift;
  indie::Tile nearPlayerTile;
  indie::Tile nearBombTile;

  player.setObjectRotation(0, indie::ELookAt::NORTH);
  newShift = player.getShiftY(0) - PLAYER_SPEED;
  player.setShiftY(0, newShift);

  if (newShift < 0.0 && y > 0) {
    nearPlayerTile = _map.at(0, x, y - 1);
    nearBombTile = _map.at(1, x, y - 1);

    // Players and Bombs are blocking movements
    if (nearPlayerTile.getType(0) == indie::OBJECTS_ID::EMPTY &&
        nearBombTile.getType(0) == indie::OBJECTS_ID::EMPTY) {
      nearPlayerTile = player;
      player.reset();
      nearPlayerTile.setShiftY(0, 1.0 + newShift);
    }
  } else if (newShift < 0.0) { player.setShiftY(0, 0.0); }
}

void indie::Game::move(size_t playerId,
                        indie::ELookAt dir) {
  static std::map<indie::ELookAt, std::function<void(indie::Tile &, size_t, size_t)> > moves_handlers = {
    { indie::ELookAt::NORTH, [this](indie::Tile &tile, size_t x, size_t y){ move_up(tile, x, y); } },
    { indie::ELookAt::SOUTH, [this](indie::Tile &tile, size_t x, size_t y){ move_down(tile, x, y); } },
    { indie::ELookAt::WEST, [this](indie::Tile &tile, size_t x, size_t y){ move_left(tile, x, y); } },
    { indie::ELookAt::EAST, [this](indie::Tile &tile, size_t x, size_t y){ move_right(tile, x, y); } },
  };

  if (moves_handlers.find(dir) == moves_handlers.end()) { return; }
  indie::Tile tile;

  for (std::size_t y = 0; y < _map.getHeight(); y++) {
    for (std::size_t x = 0; x < _map.getWidth(); x++) {
      tile = _map.at(0, x, y);
      if (tile.getType(0) == static_cast<indie::OBJECTS_ID>(playerId)) {
        moves_handlers[dir](tile, x, y);
        // check death zone
        return;
      }
    }
  }
}

void indie::Game::bomb(size_t playerId) {
  (void)playerId;
}

void indie::Game::handleEvents() {

  std::remove_if(_events.begin(), _events.end(),
  [this](Event &event)-> bool {
    std::vector<indie::Player>::iterator it;

    if (_gameState == indie::GameState::INGAME &&
        event.type == indie::EventType::ET_KEYBOARD &&
        event.action == indie::ActionType::AT_PRESSED) {
        if ((it = std::find_if(_settings.players.begin(), _settings.players.end(),
                  [&event](Player &psettings)-> bool{
                    return event.kb_key == psettings.move_left;
                  })) != _settings.players.end()) { move((*it).id, indie::ELookAt::WEST); }
        else if ((it = std::find_if(_settings.players.begin(), _settings.players.end(),
                        [&event](Player &psettings)-> bool{
                          return event.kb_key == psettings.move_right;
                        })) != _settings.players.end()) { move((*it).id, indie::ELookAt::EAST); }
        else if ((it = std::find_if(_settings.players.begin(), _settings.players.end(),
                        [&event](Player &psettings)-> bool{
                          return event.kb_key == psettings.move_down;
                        })) != _settings.players.end()) { move((*it).id, indie::ELookAt::SOUTH); }
        else if ((it = std::find_if(_settings.players.begin(), _settings.players.end(),
                        [&event](Player &psettings)-> bool{
                          return event.kb_key == psettings.move_up;
                        })) != _settings.players.end()) { move((*it).id, indie::ELookAt::NORTH); }
        else if ((it = std::find_if(_settings.players.begin(), _settings.players.end(),
                        [&event](Player &psettings)-> bool{
                          return event.kb_key == psettings.bomb;
                        })) != _settings.players.end()) { bomb((*it).id); }

      } else {
        // call gui handler
      }
    return true;
  });
}
