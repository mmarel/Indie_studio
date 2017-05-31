//
// Author: Marwane Khsime 
// Date: 2017-05-05 17:41:58 
//
// Last Modified by:   Marwane Khsime 
// Last Modified time: 2017-05-05 17:41:58
//

#ifndef GFX_HPP
# define GFX_HPP

#include <string>
#include <iostream>
#include <unordered_map>
#include <algorithm>

#include "Interfaces/IGfx.hpp"
#include "Exception/exception.hpp"
#include "Common/common.hpp"
#include "irr/irrlicht.h"

namespace indie
{

    // GLOBAL PARAMETERS
    # define SOUND_SUPPORTED    TRUE
    # define FULLSCREEN         TRUE
    # define SCREEN_WIDTH       1080
    # define SCREEN_HEIGHT      720
    # define DEBUG_MODE         TRUE
    # define DEFAULT_FONT       0
    // COLORS
    const irr::video::SColor  SBlack(255, 0, 0, 0);
    const irr::video::SColor  SWhite(255, 255, 255, 255);
    const irr::video::SColor  SRed(255, 255, 0, 0);
    const irr::video::SColor  SGreen(255, 0, 255, 0);
    const irr::video::SColor  SBlue(255, 0, 0, 255);
	const irr::video::SColor  SYellow(255, 255, 255, 0);
	const irr::video::SColor  SMagenta(255, 255, 0, 255);
	const irr::video::SColor  SCyan(255, 0, 255, 255);

    // Containers For Models
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

        irr::scene::IAnimatedMesh                 *mesh;
        std::vector<std::pair<size_t, size_t> >   frameSequences;
    };

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

        size_t                                      id;
        irr::scene::IAnimatedMeshSceneNode          *node;

    };

    class Gfx : public indie::IGfx {

        //
        // Member Functions
        //
        public:
            //  Constructor / Destructor
            Gfx();
            virtual ~Gfx();

            // Interfaces

            //  Main
            virtual void        display();
            virtual void        clear();
            //  Events
            virtual bool        pollEvents(Event &e);
            //  Sound
            virtual bool        doesSupportSound() const;
            virtual void        loadSounds(std::vector<std::pair<std::string, SoundType > > const &sounds);
            virtual void        soundControl(const Sound &sound);
            //  Sprites
            virtual void        loadSprites(std::vector<std::unique_ptr<ISprite> > &&sprites);
            //  Models
            virtual void        loadModels(std::vector<std::unique_ptr<IModel> > &&models);
            virtual void        loadObjectsId(const std::vector<std::size_t> &objects);
            //  FONTS
            virtual void        loadFonts(const std::vector<std::string> &fonts_to_load = std::vector<std::string>());
            //  GUI
            virtual void        updateGUI(IGUI &gui);
            //  Map
            virtual void        updateMap(IMap const &map);

            //  Not allowed
            void                operator=(const Gfx& gfx) = delete;
            Gfx(const Gfx &gfx) = delete;

        private:

            // Window Settings
            void                set_window_settings();

            // Game Info
            void                displayGraphicalInfos();

            // Update
            void                draw_model(const ITile &tile, std::size_t x, std::size_t y);
            void                draw_cube(const ITile &tile, std::size_t x, std::size_t y);
            void                draw_component_sprite(const IComponent &cmp);
            void                draw_component_text(const IComponent &cmp);
            void                draw_text(const std::string &txt,
                                          double x, double y,
                                          const irr::video::SColor &txtColor = irr::video::SColor(255,0,0,0),
                                          const irr::video::SColor &bgColor = irr::video::SColor(255,255,255,255));

            void                delete_old_nodes();

            // Utils
            irr::video::SColor  getSColor(const Color &color) const;
            double              get_real_posX(double pos) const noexcept;
            double              get_real_posY(double pos) const noexcept;

        //
        // Member Variables
        //
        public:

            // Irrlicht Items
            std::unique_ptr<irr::IrrlichtDevice>                _device;
            irr::video::IVideoDriver                            *_driver;
            irr::scene::ISceneManager                           *_smgr;
            irr::scene::ICameraSceneNode                        *_camera;
            irr::gui::IGUIEnvironment                           *_guienv;
            std::vector<irr::gui::IGUIFont *>                   _fonts;

            // Models Management
            std::unordered_map<std::size_t, MeshContainer>      _meshesLoaded;
            std::unordered_map<std::size_t, NodeContainer>      _nodesLoaded;
            std::vector<std::size_t> _objectsId;

        private:
            // Sprites
            std::unordered_map<std::size_t, std::vector<irr::video::ITexture *> >   _sprites;
    };

}

# endif //  GFX_HPP
