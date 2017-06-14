//
// Author: Marwane Khsime
// Date: 2017-06-04 05:32:25
//
// Last Modified by:   Marwane Khsime
// Last Modified time: 2017-06-04 05:32:25
//

#include "Game/Tile.hpp"

indie::Tile::Tile(bool hasModel,
                  std::size_t modelId,
                  const std::string &texture)

    :
      _hasModel(hasModel),
      _modelId(modelId),
      _objectId(0),
      _objectRotation(ELookAt::SOUTH),
      _objectTexture(texture),
      _doesAnimationChanged(false),
      _objectFrameLoop(std::pair<std::size_t, std::size_t>(0, 0)),
      _shiftX(0.0f),
      _shiftY(0.0f),
      _type(indie::OBJECTS_ID::EMPTY),
      _cd(0)
{

}

bool                indie::Tile::hasModel() const { return this->_hasModel; }
void                indie::Tile::setHasModel(bool hm) { this->_hasModel = hm; }

std::size_t         indie::Tile::getModelId() const { return this->_modelId; }
void                indie::Tile::setModelId(std::size_t id) { this->_modelId = id; }

std::size_t         indie::Tile::getObjectId() const { return this->_objectId; }
void                indie::Tile::setObjectId(std::size_t id) { this->_objectId = id; }

indie::ELookAt      indie::Tile::getObjectRotation() const { return this->_objectRotation; }
void                indie::Tile::setObjectRotation(indie::ELookAt look) { this->_objectRotation = look; }

std::string         indie::Tile::getObjectTexture() const { return this->_objectTexture; }
void                indie::Tile::setObjectTexture(const std::string &texture) { this->_objectTexture = texture; }

bool                indie::Tile::doesAnimationChanged() const { return this->_doesAnimationChanged; }
void                indie::Tile::setDoesAnimationChanged(bool v) { this->_doesAnimationChanged = v; }

std::pair<std::size_t, std::size_t> indie::Tile::getObjectFrameLoop() const { return this->_objectFrameLoop; }
void                indie::Tile::setObjectFrameLoop(const std::pair<std::size_t, std::size_t> &fl) { this->_objectFrameLoop = fl; }

double              indie::Tile::getShiftX() const { return this->_shiftX; }
void                indie::Tile::setShiftX(double x) { this->_shiftX = x; }

double              indie::Tile::getShiftY() const { return this->_shiftY; }
void                indie::Tile::setShiftY(double y) { this->_shiftY = y; }

indie::OBJECTS_ID indie::Tile::getType() const { return _type; }
void                indie::Tile::setType(OBJECTS_ID type) { _type = type; }

indie::Tile         &indie::Tile::operator=(const indie::Tile &other) {
  if (this != &other) {
    _hasModel = other._hasModel;
    _modelId = other._modelId;
    _objectId = other._modelId;
    _objectRotation = other._objectRotation;
    _objectTexture = other._objectTexture;
    _doesAnimationChanged = other._doesAnimationChanged;
    _objectFrameLoop = std::move(other._objectFrameLoop);
    _shiftX = other._shiftX;
    _shiftY = other._shiftY;
    _type = other._type;
  }
  return *this;
}

void              indie::Tile::reset() {
  _hasModel = false;
  _modelId = 0;
  _doesAnimationChanged = false;
  _objectFrameLoop = { 0, 0 };
  _shiftY = 0;
  _shiftX = 0;
  _type = indie::OBJECTS_ID::EMPTY;
}

std::size_t     indie::Tile::getCurrentCD() const { return _cd; }
void            indie::Tile::setCD(std::size_t cd) { _cd = cd; }
