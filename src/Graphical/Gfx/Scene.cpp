//
// Author: Marwane Khsime 
// Date: 2017-06-05 07:42:19 
//
// Last Modified by:   Marwane Khsime 
// Last Modified time: 2017-06-05 07:42:19
//

#include "Graphical/Gfx.hpp"

void    indie::Gfx::loadDome(const std::string &dome) {
    
    if (this->_dome)
        this->_dome->remove();

    if (!(this->_dome = this->_smgr->addSkyDomeSceneNode(this->_driver->getTexture(dome.c_str()),
                                                   32, 16, 1.0f, 2.0f))) {
        std::cerr << _INDIE_GFX_DOME_FAILED << std::endl;
    } else {
        this->_dome->setRotation(irr::core::vector3df({ this->_orientation[IRR_SOUTH], 0.0f, 180.0f}));
    }

}

void    indie::Gfx::updateFlor(std::size_t flor) {

    if (flor >= this->_scenesLoaded.size()) {
        std::cerr << _INDIE_GFX_SCENE_FLOR_INVALID << std::endl;
    }

    for (std::size_t i = 0; i < this->_scenesLoaded.size(); ++i) {

        for (std::size_t j = 0; j < this->_scenesLoaded.at(i)._scene.size(); ++j) {

            if (flor == i) {
                this->_scenesLoaded.at(i)._scene.at(j).second->setVisible(true);
            } else {
                this->_scenesLoaded.at(i)._scene.at(j).second->setVisible(false);
            }

        }

        if (flor == i) {
            this->_infos.flor = flor;
        }

    }

}

void    indie::Gfx::loadScene(std::vector<std::unique_ptr<indie::IScene> > &&scenes) {


    // Clear the old Scene
    for (std::size_t i = 0; i < this->_scenesLoaded.size(); ++i) {
        
        for (std::size_t j = 0; j < this->_scenesLoaded.at(i)._scene.size(); ++j) {
            this->_scenesLoaded.at(i)._scene.at(j).second->remove();
        }
        this->_scenesLoaded.at(i)._scene.clear();

    }

    this->_scenesLoaded.clear();

    for (std::size_t i = 0; i < scenes.size(); ++i) {

        indie::SceneContainer   scene_container( std::vector<
                                                    std::pair<irr::scene::IMesh *, irr::scene::IMeshSceneNode *>
                                                 >(),
                                                 scenes.at(i)->getStartX(),
                                                 scenes.at(i)->getStartY(),
                                                 scenes.at(i)->getStartZ() );

        for (std::size_t j = 0; j < scenes.at(i)->getNumberParts(); ++j) {

            irr::scene::IMesh   *mesh = this->_smgr->getMesh(scenes.at(i)->getPartAtPos(j).first.c_str());

            if (!mesh) {
                throw IndieError(_INDIE_GFX_MESH_FAILED);
            }

            irr::scene::IMeshSceneNode *node =
                this->_smgr->addMeshSceneNode(mesh,
                                              NULL,
                                              1,
                                              irr::core::vector3df(0.0f, 0.0f, 0.0f),
                                              irr::core::vector3df(0.0f, 0.0f, 0.0f));

            if (node) {
                node->setMaterialFlag(irr::video::EMF_LIGHTING, false);
                node->setMaterialTexture(0, this->_driver->getTexture(scenes.at(i)->getPartAtPos(j).second.c_str()));
            } else {
                std::cerr << _INDIE_GFX_TEXTURE_FAILED << std::endl;
            }

            node->setVisible(false);

            scene_container._scene.push_back( { mesh, node } );
        }

        this->_scenesLoaded.push_back(scene_container);
    }

}