#include "Game/Game.hpp"

std::pair<size_t, size_t> indie::Game::getNextFallingPillarPos() {
  static std::pair<size_t, size_t> fallingStonesPos = {0, 0};
  static indie::ELookAt dir = ELookAt::EAST;
  static size_t turn = 0;
  bool target = false;

  if (dir == indie::ELookAt::WEST) { fallingStonesPos.first--; }
  else if (dir == indie::ELookAt::EAST) { fallingStonesPos.first++; }
  else if (dir == indie::ELookAt::SOUTH) { fallingStonesPos.second++; }
  else if (dir == indie::ELookAt::NORTH) { fallingStonesPos.second--; }
  std::cout << " pos x " << fallingStonesPos.first << " pos y " << fallingStonesPos.second << std::endl;
  if (_map.at(0, fallingStonesPos.first, fallingStonesPos.second).getType(0) != indie::OBJECTS_ID::WALL) {
    target = true;
  }
  if (target == false) { return getNextFallingPillarPos(); }
  if (fallingStonesPos.first == _map.getWidth() - turn && dir == ELookAt::EAST) {
    dir = ELookAt::SOUTH;
  }
  else if (fallingStonesPos.second == _map.getHeight() - turn && dir == ELookAt::SOUTH) {
    dir = ELookAt::WEST;
  } else if (fallingStonesPos.first == 0 && dir == ELookAt::WEST) {
    dir = ELookAt::NORTH;
  } else if (fallingStonesPos.first == turn && dir == ELookAt::EAST) {
    dir = ELookAt::EAST;
    turn++;
  }
  return fallingStonesPos;
}

  void indie::Game::itsRainingStones() {
    std::pair<size_t, size_t> fallingStonesPos = getNextFallingPillarPos();
    size_t objectId;

    indie::Tile &target = _map.at(1, fallingStonesPos.first, fallingStonesPos.second);

    objectId = _map.newId();
    _map.addObjectById(objectId);
    target.setElem(target.getTileSize(), objectId,
                  indie::OBJECTS_ID::FALLING_PILLAR,
                  true, indie::MODELS_ID::FALLING_PILLAR_MODEL, true,
                  indie::ResourceHandler::getNextFrame(indie::OBJECTS_ID::FALLING_PILLAR, {0, 0}),
                  indie::ResourceHandler::getTexture(indie::MODELS_ID::FALLING_PILLAR_MODEL));
}

void indie::Game::fallingStones() {
  static indie::Timer CD;

  if (_settings.timer.Elapsed().count() >= 1000) {
    if (CD.Elapsed().count() >= 100) {
      std::cout << "pillier tombe\n";
      itsRainingStones();
      CD.Reset();
    }
  }
}
