#include "Game/Game.hpp"

void indie::Game::kill(indie::Tile &player) {
  std::cout << "kill player " << player.getObjectId(0) << " : this guys is a biiiiig noooob\n";
  player.setObjectFrameLoop(0, indie::ResourceHandler::getSkeletonFrame("DIE"));
  player.setDoesAnimationChanged(0, true);
}

void indie::Game::explodeBox(indie::Tile &box) {
  std::cout << "box explosion id "<< box.getObjectId(0) << "\n";
  box.setObjectFrameLoop(0, indie::ResourceHandler::getLethalFrame(indie::OBJECTS_ID::BOX));
  box.setDoesAnimationChanged(0, true);
}

void indie::Game::squareExplosion(size_t center_x, size_t center_y) {
  indie::OBJECTS_ID type;
  int target_x;
  int target_y;

  for (int c = -2; c < 3; c++) {
    for (int y = -2; y < 3; y++) {
      target_x = center_x + c;
      target_y = center_y + y;
      if (((c == 0 || c % 2 != 0) || (y == 0 || y % 2 != 0)) &&
        target_x >= 0 && target_x < _map.getWidth() && target_y + y >= 0 && target_y + y < _map.getHeight()) {
        indie::Tile &playerTarget = _map.at(0, target_x, target_y);

        type = playerTarget.getType(0);
        if (type >= indie::OBJECTS_ID::PLAYER_ONE && type <= indie::OBJECTS_ID::PLAYER_FOURTH) { kill(playerTarget); }
        else if (type == indie::OBJECTS_ID::BOX) { explodeBox(playerTarget); }
      }
    }
  }
}

void indie::Game::pikesTrap(size_t center_x, size_t center_y) {
    indie::OBJECTS_ID type;
    indie::Tile &playerTarget = _map.at(0, center_x, center_y);

    type = playerTarget.getType(0);
    if (type >= indie::OBJECTS_ID::PLAYER_ONE && type <= indie::OBJECTS_ID::PLAYER_FOURTH) { kill(playerTarget); }
    else if (type == indie::OBJECTS_ID::BOX) { explodeBox(playerTarget); }
}

void indie::Game::explode(indie::Tile &tile, size_t i, size_t center_x, size_t center_y) {
  static std::map<indie::MODELS_ID, std::function<void(size_t, size_t)> > explosionHandlers = {
    { indie::MODELS_ID::SQUAREBOMB_MODEL, [this](size_t x, size_t y){ this->squareExplosion(x, y); } },
    { indie::MODELS_ID::PIKES_MODEL_1, [this](size_t x, size_t y){ this->pikesTrap(x, y); } },
    { indie::MODELS_ID::PIKES_MODEL_2, [this](size_t x, size_t y){ this->pikesTrap(x, y); } },
    { indie::MODELS_ID::PIKES_MODEL_3, [this](size_t x, size_t y){ this->pikesTrap(x, y); } },
    { indie::MODELS_ID::PIKES_MODEL_4, [this](size_t x, size_t y){ this->pikesTrap(x, y); } },
    { indie::MODELS_ID::PIKES_MODEL_CENTER, [this](size_t x, size_t y){ this->pikesTrap(x, y); } }
  };
  indie::MODELS_ID bombType = tile.getModelId(i);

  if (explosionHandlers.find(bombType) != explosionHandlers.end()) { explosionHandlers[bombType](center_x, center_y); }
}
