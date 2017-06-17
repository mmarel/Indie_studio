#include "Game/Tile.hpp"

indie::MODELS_ID indie::Tile::getModelId(indie::OBJECTS_ID type) {
  static std::map<indie::OBJECTS_ID, indie::MODELS_ID> models = {
    { indie::OBJECTS_ID::PLAYER_ONE, indie::MODELS_ID::SKELETON_MODEL },
    { indie::OBJECTS_ID::PLAYER_TWO, indie::MODELS_ID::SKELETON_MODEL },
    { indie::OBJECTS_ID::PLAYER_THREE, indie::MODELS_ID::SKELETON_MODEL },
    { indie::OBJECTS_ID::PLAYER_FOURTH, indie::MODELS_ID::SKELETON_MODEL },
    { indie::OBJECTS_ID::BOX, indie::MODELS_ID::BOX_MODEL },
    { indie::OBJECTS_ID::SQUAREBOMB, indie::MODELS_ID::SQUAREBOMB_MODEL },
    { indie::OBJECTS_ID::TENTACLEBOMB, indie::MODELS_ID::TENTACLEBOMB_MODEL },
    { indie::OBJECTS_ID::PIKESBOMB, indie::MODELS_ID::PIKES_MODEL },
  };

  if (models.find(type) == models.end()) { return indie::MODELS_ID::UNKNOWN; }
  return models[type];
}
