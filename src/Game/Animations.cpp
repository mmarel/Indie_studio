#include "Game/Game.hpp"

void indie::Game::removeObject(indie::Tile &tile, size_t i) {
  std::cout << "remove object id " << tile.getObjectId(i) << std::endl;
  _map.deleteObjectById(tile.getObjectId(i));
  tile.deleteElement(i);
}

void indie::Game::updatePlayerAnimation(indie::Tile &tile, size_t i) {
  tile.setDoesAnimationChanged(i, true);
  tile.setObjectFrameLoop(i, indie::ResourceHandler::getSkeletonFrame("IDLE"));
}

void indie::Game::updateBombAnimation(indie::Tile &tile, size_t i, indie::OBJECTS_ID objectType, size_t x, size_t y) {
  std::pair<size_t, size_t> nextframe = indie::ResourceHandler::getNextFrame(objectType, tile.getObjectFrameLoop(i));

  if (nextframe.first == 0 && nextframe.second == 0){ return removeObject(tile, i); }
  if (indie::ResourceHandler::isFrameLethal(tile.getType(i), nextframe)) {
    explode(tile, i, x, y);
  }
  tile.setDoesAnimationChanged(i, true);
  tile.setObjectFrameLoop(i, nextframe);
}

std::vector<indie::AnimationState>::const_iterator indie::Game::getAnimationStateIt(size_t id) const {
  return std::find_if(_objectsStates.begin(), _objectsStates.end(),
          [&id](const AnimationState &animation)->bool {
            return animation.id == id;
          });
}

void indie::Game::updateAnimations() {
  indie::OBJECTS_ID objectType;
  size_t tileSize;
  std::vector<indie::AnimationState>::const_iterator animation_it;

  if (_objectsStates.size() == 0) { return; }
  for (std::size_t layer = 0; layer <= 2; layer++) {
    for (std::size_t y = 0; y < _map.getHeight(); y++) {
      for (std::size_t x = 0; x < _map.getWidth(); x++) {
        indie::Tile &tile = _map.at(layer, x, y);

        tileSize = tile.getTileSize();
        for (size_t i = 0; i < tileSize; i++) {
          objectType = tile.getType(i);
          if ((animation_it = getAnimationStateIt(tile.getObjectId(i))) != _objectsStates.end()) {

            if ((*animation_it).over) {
               std::cout << "animation  over id " << tile.getObjectId(i) << std::endl;
            } else if ((*animation_it).id == 4) { /* std::cout << "fuckiiiiiiiiiiiiiiiiiiiiiiiin bomb not over\n"; */ }
            if ((*animation_it).over && indie::ResourceHandler::isDeathFrame(tile.getModelId(i), tile.getObjectFrameLoop(i))) {
              std::cout << "object dead, should be removed\n";
              removeObject(tile, i);
            }
            else if ((*animation_it).over &&
                objectType >= indie::OBJECTS_ID::PLAYER_ONE &&
                objectType <= indie::OBJECTS_ID::PLAYER_FOURTH) { updatePlayerAnimation(tile, i); }
            else if ((*animation_it).over &&
                      objectType >= indie::OBJECTS_ID::SQUAREBOMB &&
                      objectType <= indie::OBJECTS_ID::TENTACLEBOMB) { updateBombAnimation(tile, i, objectType, x, y); }
            else if (!(*animation_it).over) { tile.setDoesAnimationChanged(i, false); }
          }
        }
      }
    }
  }
}
