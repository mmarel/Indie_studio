#include "Game/Game.hpp"

void  indie::Game::spreadBombAnimationCol(const std::size_t &x,
                                          const std::size_t &y,
                                          const std::size_t &spreadSize) {
                                            (void)x;
  for (std::size_t n = 0; n < spreadSize; n++) {
    if ((y - n) > 0) { /* set Animation (2, x, y - n) */ }
    if (n != 0 && (y + n) < _map.getHeight()) { /* set Animation (2, x, y + n) */ }
  }
}

void  indie::Game::spreadBombAnimationLine(const std::size_t &x,
                                            const std::size_t &y,
                                            const std::size_t &spreadSize) {
                                              (void)y;
  for (std::size_t n = 0; n < spreadSize; n++) {
    if ((x - n) > 0) { /* set Animation (2, x - n, y) */}
    if (n != 0 && (x + n) < _map.getWidth()) { /* set Animation (2, x + n, y) */ }
  }
}

void indie::Game::spreadBombAnimation(const std::size_t &x,
                                      const std::size_t &y,
                                      const std::size_t &spreadSize,
                                      const std::size_t &spreadWidth) {
  for (std::size_t n = 0; n < spreadWidth; n++) {
    spreadBombAnimationCol(x - n, y, spreadSize);
    spreadBombAnimationLine(x, y - n, spreadSize);
    if (n != 0) {
      spreadBombAnimationCol(x + n, y, spreadSize);
      spreadBombAnimationLine(x, y + n, spreadSize);
     }
  }
}

void  indie::Game::handleBomb(const std::size_t &x,
                              const std::size_t &y) {
  indie::Tile currentTile = _map.at(1, x, y);
  std::size_t spreadWidth = 0;
  std::size_t spreadSize = 1;
  std::size_t cd = currentTile.getCurrentCD();

  currentTile.setCD(--cd);
  if (cd > 0) { return; }
  switch (currentTile.getType()) {
    case indie::OBJECTS_ID::SQUAREBOMB:
      spreadWidth = 1;
      spreadSize = 2;
      break;
    case indie::OBJECTS_ID::PIKESBOMB:
      spreadSize = 3;
      break;
    case indie::OBJECTS_ID::TENTACLEBOMB:
      spreadSize = -1;
      break;
    case indie::OBJECTS_ID::UNKNOWN:
    case indie::OBJECTS_ID::EMPTY:
    case indie::OBJECTS_ID::PLAYER_ONE:
    case indie::OBJECTS_ID::PLAYER_TWO:
    case indie::OBJECTS_ID::PLAYER_THREE:
    case indie::OBJECTS_ID::PLAYER_FOURTH:
    case indie::OBJECTS_ID::BOX:
    case indie::OBJECTS_ID::WALL:
    default:
      break;
  }
  spreadBombAnimation(x, y, spreadSize, spreadWidth);
}

void indie::Game::handlePlayer(const std::size_t &x,
                                const std::size_t &y,
                                int playerId) {
  if (playerId > _settings.nplayers) {
    // TODO IA PART by rida
    return;
   }
  indie::Tile currentTile = _map.at(0, x, y);
  indie::ELookAt rotation = currentTile.getObjectRotation();
  indie::Tile nearPlayerTile;
  indie::Tile nearBombTile;
  double shift;

  switch (rotation) {
    case indie::ELookAt::WEST:
      if ((shift = currentTile.getShiftX()) < 0.0 && x > 0) {
        nearPlayerTile = _map.at(0, x - 1, y);
        nearBombTile = _map.at(1, x - 1, y);

        // Players and Bombs are blocking movements
        if (nearPlayerTile.getType() == indie::OBJECTS_ID::EMPTY &&
            nearBombTile.getType() == indie::OBJECTS_ID::EMPTY) {
          nearPlayerTile = currentTile;
          currentTile.reset();
          nearPlayerTile.setShiftX(1.0 + shift);
        }
      } else if (shift < 0.0) { currentTile.setShiftX(0.0); }
      break;

    case indie::ELookAt::EAST:
      if ( (shift = currentTile.getShiftX()) > 1.0 && x < (_map.getWidth() - 1)) {
        nearPlayerTile = _map.at(0, x + 1, y);
        nearBombTile = _map.at(1, x + 1, y);

        // Players and Bombs are blocking movements
        if (nearPlayerTile.getType() == indie::OBJECTS_ID::EMPTY &&
            nearBombTile.getType() == indie::OBJECTS_ID::EMPTY) {
          nearPlayerTile = currentTile;
          currentTile.reset();
          nearPlayerTile.setShiftX(shift - 1.0);
        }
      } else if (shift > 1.0) { currentTile.setShiftX(1.0); }
      break;

    case indie::ELookAt::NORTH:
      if ((shift = currentTile.getShiftY()) < 0.0 && y > 0) {
        nearPlayerTile = _map.at(0, x, y - 1);
        nearBombTile = _map.at(1, x, y - 1);

        // Players and Bombs are blocking movements
        if (nearPlayerTile.getType() == indie::OBJECTS_ID::EMPTY &&
            nearBombTile.getType() == indie::OBJECTS_ID::EMPTY) {
          nearPlayerTile = currentTile;
          currentTile.reset();
          nearPlayerTile.setShiftY(1.0 + shift);
        }
      } else if (shift < 0.0) { currentTile.setShiftY(0.0); }
      break;

    case indie::ELookAt::SOUTH:
      if ((shift = currentTile.getShiftY()) > 1.0 && y < (_map.getHeight() - 1)) {
        nearPlayerTile = _map.at(0, x, y + 1);
        nearBombTile = _map.at(1, x, y + 1);

        // Players and Bombs are blocking movements
        if (nearPlayerTile.getType() == indie::OBJECTS_ID::EMPTY &&
            nearBombTile.getType() == indie::OBJECTS_ID::EMPTY) {
          nearPlayerTile = currentTile;
          currentTile.reset();
          nearPlayerTile.setShiftY(shift - 1.0);
        }
      } else if (shift > 1.0) { currentTile.setShiftY(1.0); }
      break;

    default:
      break;
  }
}
