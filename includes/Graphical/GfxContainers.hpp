//
// Author: Marwane Khsime 
// Date: 2017-06-05 07:38:18 
//
// Last Modified by:   Marwane Khsime 
// Last Modified time: 2017-06-05 07:38:18
//

#ifndef GFX_CONTAINERS_HPP
# define GFX_CONTAINERS_HPP

#include <string>
#include <utility>
#include <vector>

#include "Interfaces/IMap.hpp"
#include "irr/irrlicht.h"

namespace indie
{

    // Gfx Infos
    struct GfxInfos {
        GfxInfos(std::size_t current_scene)
            : _current_scene(current_scene),
              _scene_loaded_once(false),
              _camera_view_point(ECAMERA_VIEW::UNDEFINED)
        {
        }
        ~GfxInfos() {}

        std::size_t  _current_scene;
        bool         _scene_loaded_once;
        ECAMERA_VIEW _camera_view_point;
    };

    // Container for Scenes
    struct SceneContainer
    {
        SceneContainer()
                    : _scene(),
                      _dome(""),
                      _startX(0.0f),
                      _startY(0.0f),
                      _startZ(0.0f)
        {

        }
        SceneContainer(const std::vector<
                                          std::pair<irr::scene::IMesh *, irr::scene::IMeshSceneNode *>
                                        > &scene,
                       const std::string &dome,
                       float x,
                       float y,
                       float z)
                    : _scene(scene),
                      _dome(dome),
                      _startX(x),
                      _startY(y),
                      _startZ(z)
        {

        }
        SceneContainer(SceneContainer &&scene, const std::string &dome, float x, float y, float z)
                    : _scene(scene._scene),
                      _dome(dome),
                      _startX(x),
                      _startY(y),
                      _startZ(z)
        {

        }
        SceneContainer(const SceneContainer &scene, const std::string &dome, float x, float y, float z)
                    : _scene(scene._scene),
                      _dome(dome),
                      _startX(x),
                      _startY(y),
                      _startZ(z)
        {

        }

        ~SceneContainer()
        {

        }

        std::vector<std::pair<irr::scene::IMesh *,
                              irr::scene::IMeshSceneNode *> >   _scene;
        std::string                                             _dome;
        float                                                   _startX;
        float                                                   _startY;
        float                                                   _startZ;
    };

    // Container For Models (meshes)
    struct  MeshContainer {

        MeshContainer()
                    : mesh(NULL), frameSequences() {
        }

        MeshContainer(irr::scene::IAnimatedMesh *_mesh,
                      std::vector<std::pair<size_t, size_t> > _frameSequences)
                      : mesh(_mesh), frameSequences(_frameSequences) {
        }

        MeshContainer(const MeshContainer &mc)
            : mesh(mc.mesh), frameSequences(mc.frameSequences) {
        }

        MeshContainer &operator=(const MeshContainer &mc) {
            this->mesh = mc.mesh;
            this->frameSequences = mc.frameSequences;
            return *this;
        }

        ~MeshContainer() {

        };

        irr::scene::IAnimatedMesh                 *mesh;
        std::vector<std::pair<size_t, size_t> >   frameSequences;
    };

    // Container for nodes (objects)
    struct  NodeContainer {

        NodeContainer()
            : id(0), node(NULL) {
        }

        NodeContainer(size_t _id, irr::scene::IAnimatedMeshSceneNode *_node)
            : id(_id), node(_node) {
        }

        NodeContainer(const NodeContainer &nc)
            : id(nc.id), node(nc.node) {
        }

        NodeContainer &operator=(const NodeContainer &nc) {
            this->id = nc.id;
            this->node = nc.node;
            return *this;
        }

        ~NodeContainer() {

        };

        size_t                                      id;
        irr::scene::IAnimatedMeshSceneNode          *node;

    };

}

#endif // GFX_CONTAINERS_HPP