//
// Author: Marwane Khsime 
// Date: 2017-06-04 06:45:22 
//
// Last Modified by:   Marwane Khsime 
// Last Modified time: 2017-06-04 06:45:22
//

#include <memory>
#include "Game/Map.hpp"

indie::Map::Map(std::size_t which_map)
    : _width(0),
      _height(0),
      _nbLayers(0),
      _sceneId(0),
      _scenePov(ECAMERA_VIEW::DEFAULT),
      _objectsId(),
      _layers(),
      _rawMap()
{

    switch (static_cast< GAME_MAP >(which_map))
    {
        case GAME_MAP::LITTLE_MAP:
            this->generate_little_map();
            break ;

        default:
            throw IndieError(_INDIE_GAME_INVALID_MAP_INDEX);
            break ;
    }

}

indie::Map::~Map() {

}

indie::ITile const &indie::Map::at(size_t layer, size_t x, size_t y) const
{
  return *this->_layers[layer][y][x];
}

std::size_t  indie::Map::getLayerNb() const { return this->_nbLayers; }

std::size_t  indie::Map::getWidth() const { return this->_width; }

std::size_t  indie::Map::getHeight() const { return this->_height; }

std::size_t  indie::Map::getSceneId() const { return this->_sceneId; }
void         indie::Map::setSceneId(std::size_t sceneId) { this->_sceneId = sceneId; }

indie::ECAMERA_VIEW    indie::Map::getPOV() const { return this->_scenePov; }
void                   indie::Map::setCameraPOV(indie::ECAMERA_VIEW pov) { this->_scenePov = pov; }

std::vector<std::size_t>    indie::Map::getObjectsId() const { return this->_objectsId; }

void                        indie::Map::addObjectById(std::size_t add) {
    if (std::find(this->_objectsId.begin(), this->_objectsId.end(), add) == this->_objectsId.end())
        this->_objectsId.push_back(add);
    else
        throw indie::IndieError(_INDIE_GAME_INVALID_OBJECT_ID);
}

void                        indie::Map::deleteObjectById(std::size_t del) {

    if (std::find(this->_objectsId.begin(), this->_objectsId.end(), del) == this->_objectsId.end())
        this->_objectsId.erase(std::remove(this->_objectsId.begin(), this->_objectsId.end(), del),
                               this->_objectsId.end());
    else
        throw indie::IndieError(_INDIE_GAME_INVALID_OBJECT_ID);
}

void                        indie::Map::setObectsId(const std::vector<std::size_t> &ids) {
    this->_objectsId = ids;
}

void         indie::Map::create_layer(std::size_t layer)
{

  this->_layers.push_back(std::vector<std::vector<std::unique_ptr<Tile> > >());

  for (size_t y = 0; y < this->_height; y++)
    {

      this->_layers[layer].push_back(std::vector<std::unique_ptr<indie::Tile>>());

      for (size_t x = 0; x < this->_width; x++)
        {
            this->_layers[layer][y].push_back(std::make_unique< Tile >());
        }

    }

}