#include "Game/Game.hpp"

void indie::Game::updatePlayerAnimation(indie::Tile &tile, size_t i) {
  tile.setDoesAnimationChanged(i, true);
  tile.setObjectFrameLoop(i, indie::Tile::getSkeletonFrame("IDLE"));
}

void indie::Game::updateBombAnimation(indie::Tile &tile, size_t i, indie::OBJECTS_ID objectType) {
  tile.setDoesAnimationChanged(i, true);
  tile.setObjectFrameLoop(i, indie::Tile::getNextFrame(objectType, tile.getObjectFrameLoop(i)));
}


std::vector<indie::AnimationState>::iterator indie::Game::getAnimationStateIt(size_t id) {
  return std::find_if(_objectsStates.begin(), _objectsStates.end(),
          [&id](AnimationState &animation)->bool {
            return animation.id == id;
          });
}

void indie::Game::updateAnimations() {
  indie::Tile tile;
  indie::OBJECTS_ID objectType;
  size_t tileSize;
  std::vector<indie::AnimationState>::iterator animation_it;

  for (std::size_t layer = 0; layer <= 2; layer++) {
    for (std::size_t y = 0; y < _map.getHeight(); y++) {
      for (std::size_t x = 0; x < _map.getWidth(); x++) {
        tile = _map.at(layer, x, y);
        tileSize = tile.getTileSize();
        for (size_t i = 0; i < tileSize; i++) {
          objectType = tile.getType(i);
          if ((animation_it = getAnimationStateIt(tile.getModelId(i))) != _objectsStates.end()) {
            // check death
            /*if (animation.over && indie::Tile::isDeathFrame(objectType, tile->getObjectFrameLoop(i))) {
              remove object
            }*/
            if ((*animation_it).over &&
                objectType >= indie::OBJECTS_ID::PLAYER_ONE &&
                objectType <= indie::OBJECTS_ID::PLAYER_FOURTH) { updatePlayerAnimation(tile, i); }
            else if ((*animation_it).over &&
                      objectType >= indie::OBJECTS_ID::SQUAREBOMB &&
                      objectType <= indie::OBJECTS_ID::TENTACLEBOMB) { updateBombAnimation(tile, i, objectType); }
            else if (!(*animation_it).over) { tile.setDoesAnimationChanged(i, false); }
          }
        }
      }
    }
  }
}
