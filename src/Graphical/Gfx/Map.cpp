//
// Author: Marwane Khsime 
// Date: 2017-05-22 19:17:54 
//
// Last Modified by:   Marwane Khsime 
// Last Modified time: 2017-05-22 19:17:54
//

#include "Graphical/Gfx.hpp"

void    indie::Gfx::draw_cube(const ITile &tile, std::size_t x, std::size_t z) {
    (void)tile;
    (void)x;
    (void)z;
}

void    indie::Gfx::draw_model(const ITile &tile, std::size_t x, std::size_t z) {

    if (this->_nodesLoaded.count(tile.getObjectId()) != 0) {

        // Just set Position, Rotation and frames
        irr::scene::IAnimatedMeshSceneNode  *node = this->_nodesLoaded[tile.getObjectId()].node;

        if (tile.doesAnimationChanged())
            node->setFrameLoop(static_cast< irr::s32 >(tile.getObjectFrameLoop().first),
                               static_cast< irr::s32 >(tile.getObjectFrameLoop().second));

        node->setPosition(irr::core::vector3df(this->_scenesLoaded[this->_infos._current_scene]._startX + static_cast< float >(x),
                                               this->_scenesLoaded[this->_infos._current_scene]._startY,
                                               this->_scenesLoaded[this->_infos._current_scene]._startZ + static_cast< float >(z)));

        node->setRotation(irr::core::vector3df(0.0f, this->_orientation[static_cast<std::size_t>(tile.getObjectRotation())], 0.0f));

    } else {

        // We create a new one
        NodeContainer           newModel;
        irr::core::vector3df    position(this->_scenesLoaded[this->_infos._current_scene]._startX + static_cast< float >(x),
                                         this->_scenesLoaded[this->_infos._current_scene]._startY,
                                         this->_scenesLoaded[this->_infos._current_scene]._startZ + static_cast< float >(z));
        irr::core::vector3df    rotation(0.0f, this->_orientation[static_cast<std::size_t>(tile.getObjectRotation())], 0.0f);

        if ((newModel.node =
                this->_smgr->addAnimatedMeshSceneNode(this->_meshesLoaded[tile.getModelId()].mesh,
                                                      NULL,
                                                      1,
                                                      position,
                                                      rotation)) == nullptr)
                throw IndieError(_INDIE_GFX_TEXTURE_FAILED);

        if (newModel.node)
            {
                newModel.node->setMaterialFlag(irr::video::EMF_LIGHTING, false);
                newModel.node->setMD2Animation(irr::scene::EMAT_STAND);
                newModel.node->setMaterialTexture(0, this->_driver->getTexture(tile.getObjectTexture().c_str()) );
            }

        newModel.id = tile.getObjectId();
        newModel.node->setFrameLoop(static_cast< irr::s32 >(tile.getObjectFrameLoop().first),
                                    static_cast< irr::s32 >(tile.getObjectFrameLoop().second));
        newModel.node->setCurrentFrame(static_cast< float >(tile.getObjectFrameLoop().first));
        this->_nodesLoaded[tile.getObjectId()] = newModel;
    }

}

void    indie::Gfx::delete_old_nodes() {

    std::unordered_map<std::size_t, NodeContainer>::iterator it = this->_nodesLoaded.begin();

    while (it != this->_nodesLoaded.end()) {

       if ((std::find(this->_objectsId.begin(), this->_objectsId.end(), it->second.id)) == this->_objectsId.end())
       {
           it->second.node->remove();
           it = this->_nodesLoaded.erase(it);
       } else {
           ++it;
       }

    }

}

void    indie::Gfx::updateMap(const IMap &map) {

    std::size_t nbLayers    = map.getLayerNb();
    std::size_t map_width   = map.getWidth();
    std::size_t map_height  = map.getHeight();

    // If the scene has changed, we update it
    if (map.getSceneId() != this->_infos._current_scene || !this->_infos._scene_loaded_once) {
        this->update_scene(map.getSceneId());
        this->_infos._current_scene = map.getSceneId();
        this->_infos._scene_loaded_once = true;
    }

    (void)nbLayers;
    (void)map_width;
    (void)map_height;

    // Delete nodes unused
    this->delete_old_nodes();

    // Layers
    for (std::size_t layer = 0; layer < nbLayers; ++layer) {

        for (std::size_t y = 0; y < map_height; ++y) {

            for (std::size_t x = 0; x < map_width; ++x) {

                // To change when tile will be ready
                // Tile   tile = map.at(layer, x, y);

                if (map.at(layer, x, y).hasModel())
                    this->draw_model(map.at(layer, x, y), x, y);
                else
                    this->draw_cube(map.at(layer, x ,y ), x, y);

            }

        }

    }

    return ;
}