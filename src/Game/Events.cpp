#include "Game/Game.hpp"

indie::Tile &indie::Game::move_left(indie::Tile &player,
                                    size_t x, size_t y) {
  double newShift;
  bool tangible;

  newShift = player.getShiftX(0) - PLAYER_SPEED;
  tangible = (x == 0 || _map.at(0, x - 1, y).isTangible(0) || _map.at(1, x - 1, y).isTangible(0));
  if (newShift < 0.0 && !tangible) {
      std::cout << "go left cell\n";
      indie::Tile &nearPlayerTile = _map.at(0, x - 1, y);

      nearPlayerTile = player;
      player.reset();
      nearPlayerTile.setShiftX(0, 1.0 + newShift);
      return nearPlayerTile;
    }
    else if (tangible) { player.setShiftX(0, 0.0); }
    else if (tangible && newShift < 0.3) { player.setShiftX(0, 0.3); }
    else if (newShift >= 0.0) { player.setShiftX(0, newShift); }
  return player;
}

indie::Tile &indie::Game::move_right(indie::Tile &player,
                                      size_t x, size_t y) {
  double newShift;
  bool tangible;

  newShift = player.getShiftX(0) + PLAYER_SPEED;
  tangible = (x == (_map.getWidth() - 1) || _map.at(0, x + 1, y).isTangible(0) || _map.at(1, x + 1, y).isTangible(0));
  if (newShift >= 1.0 && !tangible) {
      std::cout << "go right cell\n";
      indie::Tile &nearPlayerTile = _map.at(0, x + 1, y);

      nearPlayerTile = player;
      player.reset();
      nearPlayerTile.setShiftX(0, newShift - 1.0);
      return nearPlayerTile;
  }
  else if (tangible) { player.setShiftX(0, 0.0); }
  else if (tangible && newShift > 0.7) { player.setShiftX(0, 0.7); }
  else if (newShift < 1.0) { player.setShiftX(0, newShift); }
  return player;
}

indie::Tile &indie::Game::move_down(indie::Tile &player,
                                    size_t x, size_t y) {
  double newShift;
  bool tangible;

  newShift = player.getShiftY(0) + PLAYER_SPEED;
  tangible = (y == (_map.getHeight() - 1) || _map.at(0, x, y + 1).isTangible(0) || _map.at(1, x, y + 1).isTangible(0));
  if (newShift >= 1.0 && !tangible) {
      std::cout << "go down cell\n";
      indie::Tile &nearPlayerTile = _map.at(0, x, y + 1);

      nearPlayerTile = player;
      player.reset();
      nearPlayerTile.setShiftY(0, newShift - 1.0);
      return nearPlayerTile;
    }
    else if (tangible) { player.setShiftY(0, 0.0); }
    else if (tangible && newShift > 0.7) { player.setShiftY(0, 0.7); }
    else if (newShift < 1.0) { player.setShiftY(0, newShift); }
  return player;
}

indie::Tile &indie::Game::move_up(indie::Tile &player,
                                  size_t x, size_t y) {
  double newShift;
  bool tangible;

  newShift = player.getShiftY(0) - PLAYER_SPEED;
  tangible = (y == 0 || _map.at(0, x, y - 1).isTangible(0) || _map.at(1, x, y - 1).isTangible(0));
  if (newShift < 0.0 && !tangible) {
      std::cout << "go up cell\n";
      indie::Tile &nearPlayerTile = _map.at(0, x, y - 1);

      nearPlayerTile = player;
      player.reset();
      nearPlayerTile.setShiftY(0, 1.0 + newShift);
      return nearPlayerTile;
  }
  else if (tangible) { player.setShiftY(0, 0.0); }
  else if (tangible && newShift < 0.3) { player.setShiftY(0, 0.3); }
  else if (newShift >= 0.0) { player.setShiftY(0, newShift); }
  return player;
}

void indie::Game::move(size_t playerId,
                        indie::ELookAt dir) {
  static std::map<indie::ELookAt, std::function<Tile &(indie::Tile &, size_t, size_t)> > moves_handlers = {
    { indie::ELookAt::NORTH, [this](indie::Tile &tile, size_t x, size_t y)->indie::Tile &{ return move_up(tile, x, y); } },
    { indie::ELookAt::SOUTH, [this](indie::Tile &tile, size_t x, size_t y)->indie::Tile &{ return move_down(tile, x, y); } },
    { indie::ELookAt::WEST, [this](indie::Tile &tile, size_t x, size_t y) ->indie::Tile &{ return move_left(tile, x, y); } },
    { indie::ELookAt::EAST, [this](indie::Tile &tile, size_t x, size_t y) ->indie::Tile &{ return move_right(tile, x, y); } },
  };

  if (moves_handlers.find(dir) == moves_handlers.end()) { return; }
  for (std::size_t y = 0; y < _map.getHeight(); y++) {
    for (std::size_t x = 0; x < _map.getWidth(); x++) {
      indie::Tile &tile = _map.at(0, x, y);
      if (tile.getType(0) == static_cast<indie::OBJECTS_ID>(playerId)) {
        indie::Tile &ntile = moves_handlers[dir](tile, x, y);
        std::pair<size_t, size_t> current_frame;
        std::pair<size_t, size_t> run_frame = indie::ResourceHandler::getSkeletonFrame("RUN");

        ntile.setObjectRotation(0, dir);
        current_frame = ntile.getObjectFrameLoop(0);
        if (current_frame != run_frame) {
          ntile.setDoesAnimationChanged(0, true);
          ntile.setObjectFrameLoop(0, run_frame);
        }
        return;
      }
    }
  }
}

void indie::Game::SquareBomb(indie::Tile &bombTile) {
  bombTile.setModelId(0, indie::MODELS_ID::SQUAREBOMB_MODEL);
  bombTile.setObjectTexture(0, indie::ResourceHandler::getTexture(indie::MODELS_ID::SQUAREBOMB_MODEL));
}

void indie::Game::bomb(size_t playerId) {
  static std::map<indie::OBJECTS_ID, std::function<void(indie::Tile &)> > bombHandlers = {
    { indie::OBJECTS_ID::SQUAREBOMB, [this](indie::Tile &tile){ this->SquareBomb(tile); } },
    { indie::OBJECTS_ID::PIKESBOMB, [this](indie::Tile &tile){ this->SquareBomb(tile); } },
    { indie::OBJECTS_ID::TENTACLEBOMB, [this](indie::Tile &tile){ this->SquareBomb(tile); } }
  };
  indie::OBJECTS_ID type = getBombType(playerId);

  for (std::size_t y = 0; y < _map.getHeight(); y++) {
    for (std::size_t x = 0; x < _map.getWidth(); x++) {
      if (_map.at(0, x, y).getType(0) == static_cast<indie::OBJECTS_ID>(playerId)) {
        if (_map.at(1, x, y).getType(0) != indie::OBJECTS_ID::EMPTY) { return; }
        indie::Tile &bombTile = _map.at(1, x, y);

        size_t objectId = _map.newId();
        bombHandlers[type](bombTile);
        bombTile.setHasModel(0, true);
        bombTile.setDoesAnimationChanged(0, true);
        bombTile.setObjectId(0, objectId);
        bombTile.setType(0, type);
        _map.addObjectById(objectId);
        bombTile.setObjectFrameLoop(0, indie::ResourceHandler::getNextFrame(type, {0, 0}));
        return;
      }
    }
  }
}

void indie::Game::handleEvents() {
  std::for_each(_events.begin(), _events.end(),
  [this](const Event &event) {
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

      } else { std::cout << "this is not my event biatch\n"; _gui.notifyEvent(event); }
  });
  _events.clear();
}
