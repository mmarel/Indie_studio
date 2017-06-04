//
// Author: Marwane Khsime 
// Date: 2017-06-04 05:32:25 
//
// Last Modified by:   Marwane Khsime 
// Last Modified time: 2017-06-04 05:32:25
//

#include "Common/Tile.hpp"

indie::Tile::Tile(const Color &color,
                  bool hasModel,
                  std::size_t meshId,
                  std::size_t modelId,
                  ELookAt rotation,
                  const std::string &texture,
                  bool animationChanged,
                  std::pair<size_t, size_t> frameLoop,
                  double shiftX,
                  double shiftY)

    : _color(color),
      _hasModel(hasModel),
      _meshId(meshId),
      _modelId(modelId),
      _modelRotation(rotation),
      _modelTexture(texture),
      _doesAnimationChanged(animationChanged),
      _modelFrameLoop(frameLoop),
      _shiftX(shiftX),
      _shiftY(shiftY)

{

}

indie::Color        indie::Tile::getColor() const { return this->_color; }

bool                indie::Tile::hasModel() const { return this->_hasModel; }

std::size_t         indie::Tile::getMeshId() const { return this->_meshId; }

std::size_t         indie::Tile::getModelId() const { return this->_modelId; }

indie::ELookAt      indie::Tile::getModelRotation() const { return this->_modelRotation; }

std::string         indie::Tile::getModelTexture() const { return this->_modelTexture; }

bool                indie::Tile::doesAnimationChanged() const { return this->_doesAnimationChanged; }

std::pair<std::size_t, std::size_t> indie::Tile::getModelFrameLoop() const { return this->_modelFrameLoop; }

double              indie::Tile::getShiftX() const { return this->_shiftX; }

double              indie::Tile::getShiftY() const { return this->_shiftY; }