//
// Author: Marwane Khsime 
// Date: 2017-06-08 00:50:54 
//
// Last Modified by:   Marwane Khsime 
// Last Modified time: 2017-06-08 00:50:54
//

#include "Game/Map.hpp"

void    indie::Map::generate_little_map() {

    this->_rawMap = std::vector<std::vector< int > >
      ({
        std::vector< int >({ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 }),
        std::vector< int >({ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 }),
        std::vector< int >({ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 }),
        std::vector< int >({ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 }),
        std::vector< int >({ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 }),
        std::vector< int >({ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 }),
        std::vector< int >({ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 }),
        std::vector< int >({ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 }),
        std::vector< int >({ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 }),
        std::vector< int >({ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 }),
        std::vector< int >({ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 }),
        std::vector< int >({ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 }),
        std::vector< int >({ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 })
      });

    this->_width = 11;
    this->_height = 13;
    this->_nbLayers = 1;
    this->_sceneId = 0;
    this->create_layer(0);

    this->_layers[0][0][0]->setHasModel(true);
    this->_layers[0][0][0]->setDoesAnimationChanged(false);
    this->_layers[0][0][0]->setObjectRotation(ELookAt::SOUTH);
    this->_layers[0][0][0]->setObjectTexture("Textures/SkeletonMage/Blue.png");
    this->_layers[0][0][0]->setModelId(static_cast< std::size_t >(MODELS_ID::SKELETON_MODEL));
    this->_layers[0][0][0]->setObjectId(1);
    this->_layers[0][0][0]->setObjectFrameLoop(std::pair<std::size_t, std::size_t>(177, 252));

    this->_layers[0][0][4]->setHasModel(true);
    this->_layers[0][0][4]->setDoesAnimationChanged(false);
    this->_layers[0][0][4]->setObjectRotation(ELookAt::SOUTH);
    this->_layers[0][0][4]->setObjectTexture("Map/Box.png");
    this->_layers[0][0][4]->setModelId(static_cast< std::size_t >(MODELS_ID::BOX_MODEL));
    this->_layers[0][0][4]->setObjectId(2);
    this->_layers[0][0][4]->setObjectFrameLoop(std::pair<std::size_t, std::size_t>(0, 50));

}