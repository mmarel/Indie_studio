//
// Author: Marwane Khsime
// Date: 2017-06-04 05:32:25
//
// Last Modified by:   Marwane Khsime
// Last Modified time: 2017-06-04 05:32:25
//

#include "Game/Tile.hpp"

indie::Tile::Tile()

    :
      _hasModel( { false }),
      _modelId( { 0 }),
      _objectId( { 0 }),
      _objectRotation( { indie::ELookAt::SOUTH }),
      _objectTexture( { "" }),
      _doesAnimationChanged( { false }),
      _objectFrameLoop({ { 0, 0 } }),
      _shiftX( { 0.5 } ),
      _shiftY( { 0.5 }),
      _type( { indie::OBJECTS_ID::EMPTY })
{

}

std::size_t         indie::Tile::getTileSize() const { return this->_hasModel.size(); }

bool                indie::Tile::hasModel(std::size_t at) const { return this->_hasModel.at(at); }
void                indie::Tile::setHasModel(std::size_t at, bool hm) { this->_hasModel.at(at) = hm; }

std::size_t         indie::Tile::getModelId(std::size_t at) const { return this->_modelId.at(at); }
void                indie::Tile::setModelId(std::size_t at, std::size_t id) { this->_modelId.at(at) = id; }
std::size_t         indie::Tile::getObjectId(std::size_t at) const { return this->_objectId.at(at); }
void                indie::Tile::setObjectId(std::size_t at, std::size_t id) { this->_objectId.at(at) = id; }

indie::ELookAt      indie::Tile::getObjectRotation(std::size_t at) const { return this->_objectRotation.at(at); }
void                indie::Tile::setObjectRotation(std::size_t at, indie::ELookAt look) { this->_objectRotation.at(at) = look; }

std::string         indie::Tile::getObjectTexture(std::size_t at) const { return this->_objectTexture.at(at); }
void                indie::Tile::setObjectTexture(std::size_t at, const std::string &texture) { this->_objectTexture.at(at) = texture; }

bool                indie::Tile::doesAnimationChanged(std::size_t at) const { return this->_doesAnimationChanged.at(at); }
void                indie::Tile::setDoesAnimationChanged(std::size_t at, bool v) { this->_doesAnimationChanged.at(at) = v; }

std::pair<std::size_t, std::size_t> indie::Tile::getObjectFrameLoop(std::size_t at) const { return this->_objectFrameLoop.at(at); }
void                indie::Tile::setObjectFrameLoop(std::size_t at, const std::pair<std::size_t, std::size_t> &fl) { this->_objectFrameLoop.at(at) = fl; }

double              indie::Tile::getShiftX(std::size_t at) const { return this->_shiftX.at(at); }
void                indie::Tile::setShiftX(std::size_t at, double x) { this->_shiftX.at(at) = x; }

double              indie::Tile::getShiftY(std::size_t at) const { return this->_shiftY.at(at); }
void                indie::Tile::setShiftY(std::size_t at, double y) { this->_shiftY.at(at) = y; }

indie::OBJECTS_ID indie::Tile::getType(std::size_t at) const { return this->_type.at(at); }
void                indie::Tile::setType(std::size_t at, OBJECTS_ID type) { this->_type.at(at) = type; }

indie::Tile         &indie::Tile::operator=(const indie::Tile &other) {
  if (this != &other) {
    _hasModel = other._hasModel;
    _modelId = other._modelId;
    _objectId = other._modelId;
    _objectRotation = other._objectRotation;
    _objectTexture = other._objectTexture;
    _doesAnimationChanged = other._doesAnimationChanged;
    _objectFrameLoop = other._objectFrameLoop;
    _shiftX = other._shiftX;
    _shiftY = other._shiftY;
    _type = other._type;
  }
  return *this;
}

void              indie::Tile::reset() {
  this->_hasModel =  { false };
  this->_modelId = { 0 };
  this->_doesAnimationChanged = { false };
  this->_objectFrameLoop =  { { 0,0 } };
  this->_shiftY = { 0.0 };
  this->_shiftX = { 0.0 };
  this->_type = { indie::OBJECTS_ID::EMPTY };
}
