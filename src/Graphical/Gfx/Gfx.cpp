//
// Author: Marwane Khsime 
// Date: 2017-05-05 17:53:29 
//
// Last Modified by:   Marwane Khsime 
// Last Modified time: 2017-05-05 17:53:29
//

#include "Graphical/Gfx.hpp"

indie::Gfx::Gfx()

    // irr::createDevice (deviceType, windowSize, bits, fullscreen, stencilbuffer, vsync, receiver)


    try : _device(irr::createDevice (   irr::video::EDT_OPENGL,
                                        irr::core::dimension2d<irr::u32>(SCREEN_WIDTH, SCREEN_HEIGHT),
                                        32,
                                        false,
                                        true,
                                        false,
                                        0) ),
          _driver(this->_device->getVideoDriver()),
          _smgr(this->_device->getSceneManager()),
          _camera(),
          _guienv(this->_device->getGUIEnvironment()),
          _fonts(),
          _meshesLoaded(),
          _nodesLoaded(),
          _objectsId(),
          _sprites()

    {
        
        std::cout << "Launching Irrlicht GFX" << std::endl;

        this->_device->setWindowCaption(L"BAUNTLET");

        // TESTING MESH ####################################

        // std::vector<std::pair<size_t, size_t> > fm = { { 0, 10 }  };
        // std::vector<unique_ptr<IModel> > &&models = { Model("models/SkeletonWizard.b3d", fm)}
        irr::scene::IAnimatedMesh   *mesh = this->_smgr->getMesh("Models/SkeletonMage/SkeletonMage.b3d");

        if (!mesh) {
            throw IndieError(_INDIE_GFX_MESH_FAILED);
        }

        irr::scene::IAnimatedMeshSceneNode *node =
            this->_smgr->addAnimatedMeshSceneNode(mesh,
                                                  NULL,
                                                  1,
                                                  irr::core::vector3df(0.0f, 0.0f, 10.0f),
                                                  irr::core::vector3df(0.0f, 180.0f, 0.0f));

        if (node) {
            node->setMaterialFlag(irr::video::EMF_LIGHTING, false);
            node->setMD2Animation(irr::scene::EMAT_STAND);
            node->setMaterialTexture(0, this->_driver->getTexture("Textures/SkeletonMage/Blue.png"));
        } else {
            std::cerr << _INDIE_GFX_TEXTURE_FAILED << std::endl;
        }

        irr::SKeyMap keyMap[5];

        keyMap[0].Action = irr::EKA_MOVE_FORWARD;
        keyMap[0].KeyCode = irr::KEY_KEY_Z;
        keyMap[1].Action = irr::EKA_MOVE_BACKWARD;
        keyMap[1].KeyCode = irr::KEY_KEY_S;
        keyMap[2].Action = irr::EKA_STRAFE_LEFT;
        keyMap[2].KeyCode = irr::KEY_KEY_Q;
        keyMap[3].Action = irr::EKA_STRAFE_RIGHT;
        keyMap[3].KeyCode = irr::KEY_KEY_D;
        keyMap[4].Action = irr::EKA_JUMP_UP;
        keyMap[4].KeyCode = irr::KEY_SPACE;

        // this->_camera = this->_smgr->addCameraSceneNode(NULL,
        //                                                 //                    x     y     z
        //                                                 irr::core::vector3df(-5.0f, 1.0f, 0.0f), // Position
        //                                                 irr::core::vector3df(0.0f, 0.0f, 0.0f)  // Angle
        //                                                 );

        // Uncomment for use fps camera (can move, for debug)
        this->_camera = this->_smgr->addCameraSceneNodeFPS(0, 100.0f, 0.025f, -1, keyMap, 5);

        this->set_window_settings();

        // This loop is just for testing
        while (this->_device->run())
        {

            this->_driver->beginScene(true, true, SBlack);

            this->_smgr->drawAll();

            #if DEBUG_MODE
                this->displayGraphicalInfos();
            #endif

            this->_guienv->drawAll();

            this->_driver->endScene();

        }

        //########################################## END TEST

    }

    catch (const std::exception &err) {
        std::cerr << err.what() << std::endl;
        throw err;
}

indie::Gfx::~Gfx() {}

void    indie::Gfx::display() {
    std::cout << "display" << std::endl;
}

void    indie::Gfx::clear() {
    std::cout << "clear" << std::endl;
}

void    indie::Gfx::set_window_settings() {

    // Hide Cursor
    this->_device->getCursorControl()->setVisible(false);

    // Load Default Font
    this->loadFonts();
}

void    indie::Gfx::displayGraphicalInfos() {

    //  Camera Position
    irr::core::vector3df posCam = this->_camera->getPosition();
    std::string camTxt = "CAMERA POS ( " +  std::to_string(posCam.X) + ", " +
                                        std::to_string(posCam.Y) + ", " +
                                        std::to_string(posCam.Z) + " )";
    this->draw_text(camTxt, 0.0f, 0.0f, SCyan, SBlack);

    irr::core::vector3df pos = this->_camera->getAbsolutePosition();
    irr::core::vector3df target = this->_camera->getTarget();
    irr::core::vector3df dir = target - pos;

    std::string dirTxt = "CAMERA ANGLE ( " +  std::to_string(dir.X) + ", " +
                                              std::to_string(dir.Y) + ", " +
                                              std::to_string(dir.Z) + " )";
    this->draw_text(dirTxt, 0.0f, 0.025f, SCyan, SBlack);

    //  FPS
    std::string fpsTxt("FPS : " + std::to_string(this->_driver->getFPS()));
    this->draw_text(fpsTxt, 0.0f, 0.050f, SCyan, SBlack);
}
