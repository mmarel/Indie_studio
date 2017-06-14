//
// Author: Marwane Khsime 
// Date: 2017-05-29 18:49:20 
//
// Last Modified by:   Marwane Khsime 
// Last Modified time: 2017-05-29 18:49:20
//

#include "Graphical/Gfx.hpp"

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

void        indie::Gfx::refresh_objects_id(const std::vector<std::size_t> &objects) {
    this->_objectsId.clear();
    this->_objectsId = objects;
}

void        indie::Gfx::loadModels(std::unique_ptr<std::vector<std::unique_ptr<IModel> > > models) {

    // Clear old Models
    this->_meshesLoaded.clear();

    // Load new ones
    for (std::size_t i = 0; i < models->size(); ++i) {

        MeshContainer   container;

        if (!(container.mesh = this->_smgr->getMesh(models->at(i)->getMeshPath().c_str())))
            throw indie::IndieError(_INDIE_GFX_MESH_FAILED);

        container.frameSequences = models->at(i)->getAnimationsFrames();

        this->_meshesLoaded[i] = container;
    }

}
