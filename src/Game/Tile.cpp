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
      _color(Color::Black),
      _hasModel(hasModel),
      _modelId(modelId),
      _objectId(0),
      _objectRotation(ELookAt::SOUTH),
      _objectTexture(texture),
      _doesAnimationChanged(false),
      _objectFrameLoop(std::pair<std::size_t, std::size_t>(0, 0)),
      _shiftX(0.0f),
      _shiftY(0.0f)
{

}

indie::Color        indie::Tile::getColor() const { return this->_color; }
void                indie::Tile::setColor(const Color &color) { this->_color = color; }

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