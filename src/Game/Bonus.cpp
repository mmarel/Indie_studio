#include "Game/Game.hpp"

void indie::Game::updateScore(size_t id, int points) {
  std::find_if(_players.begin(), _players.end(),
  [&id, &points](std::unique_ptr<indie::Player> &player){
    if (player->hasBomb(id)) {
      player->updateScore(points);
      return true;
    }
    return false;
  });
}

void indie::Game::deleteBombSaves(size_t id) {
  std::find_if(_players.begin(), _players.end(),
  [&id](std::unique_ptr<indie::Player> &player){
    if (player->hasBomb(id)) {
      player->removeBomb(id);
      return true;
    }
    return false;
  });
}


void indie::Game::popBonus(indie::Tile &tile, size_t i) {
  size_t objectId;
  size_t ret;

  ret = rand() % 20;
  if (ret > 5) { return tile.deleteElement(i); }
  objectId = _map.newId();
  _map.addObjectById(objectId);
  if (ret <= 3) {
    tile.setElem(i, objectId,
                indie::OBJECTS_ID::BONUS_SQUAREB,
                true, indie::MODELS_ID::BONUS_SQUAREB_MODEL, true, {0, 0},
                indie::ResourceHandler::getTexture(indie::MODELS_ID::BONUS_SQUAREB_MODEL));
  } else if (ret == 4) {
    tile.setElem(i, objectId,
                indie::OBJECTS_ID::BONUS_TENTACLEB,
                true, indie::MODELS_ID::BONUS_TENTACLEB_MODEL, true, {0, 0},
                indie::ResourceHandler::getTexture(indie::MODELS_ID::BONUS_TENTACLEB_MODEL));
  }
}
