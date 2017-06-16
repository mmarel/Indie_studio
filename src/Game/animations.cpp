#include "Game/Game.hpp"

void indie::Game::updatePlayerAnimation(indie::Tile &tile, size_t i) {
  std::cout << "updatePlayerAnimation" << std::endl;
  tile.setDoesAnimationChanged(i, true);
  tile.setObjectFrameLoop(i, indie::Tile::getSkeletonFrame("RUN"));
}

void indie::Game::updateBombAnimation(indie::Tile &tile, size_t i, indie::OBJECTS_ID objectType) {
  tile.setDoesAnimationChanged(i, true);
  tile.setObjectFrameLoop(i, indie::Tile::getNextFrame(objectType, tile.getObjectFrameLoop(i)));
}

std::vector<indie::AnimationState>::const_iterator indie::Game::getAnimationStateIt(size_t id) const {
  std::cout << "look for animation id " << id << std::endl;
  return std::find_if(_objectsStates.begin(), _objectsStates.end(),
          [&id](const AnimationState &animation)->bool {
            return animation.id == id;
          });
}

void indie::Game::removeObject(indie::Tile &tile, size_t i) {
  _map.deleteObjectById(tile.getObjectId(i));
  tile.deleteElement(i);
}

void indie::Game::updateAnimations() {
  std::cout << "update Animations count: " << _objectsStates.size() << std::endl;
  indie::OBJECTS_ID objectType;
  size_t tileSize;
  std::vector<indie::AnimationState>::const_iterator animation_it;

  if (_objectsStates.size() == 0) { return; }
  for (std::size_t layer = 0; layer <= 0; layer++) {
    for (std::size_t y = 0; y < _map.getHeight(); y++) {
      for (std::size_t x = 0; x < _map.getWidth(); x++) {
        indie::Tile &tile = _map.at(layer, x, y);
        tileSize = tile.getTileSize();
        for (size_t i = 0; i < tileSize; i++) {
          objectType = tile.getType(i);

          if ((animation_it = getAnimationStateIt(tile.getObjectId(i))) != _objectsStates.end()) {
            std::cout << "animtion found " << std::endl;
            if ((*animation_it).over) { std::cout << "oveeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeer\n\n\n";}
            if ((*animation_it).over && indie::Tile::isDeathFrame(tile.getModelId(i), tile.getObjectFrameLoop(i))) {
              removeObject(tile, i);
            }
            else if ((*animation_it).over &&
                objectType >= indie::OBJECTS_ID::PLAYER_ONE &&
                objectType <= indie::OBJECTS_ID::PLAYER_FOURTH) { updatePlayerAnimation(tile, i); }
            else if ((*animation_it).over &&
                      objectType >= indie::OBJECTS_ID::SQUAREBOMB &&
                      objectType <= indie::OBJECTS_ID::TENTACLEBOMB) { updateBombAnimation(tile, i, objectType); }
            else if (!(*animation_it).over) { std::cout << "not over" << std::endl; tile.setDoesAnimationChanged(i, false); }
          }
        }
      }
    }
  }
}
