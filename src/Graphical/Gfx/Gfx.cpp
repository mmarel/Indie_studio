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
          // Irrlicht Items
          _driver(this->_device->getVideoDriver()),
          _smgr(this->_device->getSceneManager()),
          _camera(),
          _guienv(this->_device->getGUIEnvironment()),
          // Font
          _fonts(),
          // Scenes Management
          _scenesLoaded(),
          _dome(),
          // Models Management
          _meshesLoaded(),
          _nodesLoaded(),
          _objectsId(),
          // Events Management
          _eventsOverlay(),
          // Sound
          _soundManager(),
          // Sprites Management
          _sprites(),
          // Utils
          // ------------  N      E       S      W
          _orientation( { 180.0f, 270.0f, 0.0f, 90.0f }),
          _infos(0)
    {

        std::cout << "Launching Irrlicht GFX" << std::endl;

        this->_device->setWindowCaption(L"BAUNTLET");

        // TESTING MESH ####################################

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
 
        this->test_drawing_map();

        indie::Map  map(0);
        std::unique_ptr<indie::Model>   mod1 = std::make_unique<indie::Model>("Models/SkeletonMage/SkeletonMage.b3d",
                                                        std::vector<std::pair<size_t, size_t> >( { std::make_pair(177, 252) } ));

        std::unique_ptr<indie::Model>   mod2 = std::make_unique<indie::Model>("Map/Box.md3",
                                                        std::vector<std::pair<size_t, size_t> >( { std::make_pair(0, 30) } ));

        std::vector<std::unique_ptr<indie::IModel> >   models;

        models.push_back(std::move(mod1));
        models.push_back(std::move(mod2));

        this->loadModels(std::move(models));

        // This loop is just for testing
        while (this->_device->run())
        {
            this->loadObjectsId(std::vector<std::size_t>( { 1, 2 } ) );
            this->updateMap(map);
            this->display();
        }

        //########################################## END TEST

    }

    catch (const std::exception &err) {
        std::cerr << err.what() << std::endl;
        throw err;
}

indie::Gfx::~Gfx() {}

void    indie::Gfx::display() {

    if (this->_device->run())
    {

        this->_driver->beginScene(true, true, SBlack);

        this->_smgr->drawAll();

        #if DEBUG_MODE
            this->displayGraphicalInfos();

            indie::Event    e;

            this->pollEvents(e);
        #endif

        this->_guienv->drawAll();

        this->_driver->endScene();

    }   else {

        std::cerr << _INDIE_GFX_DEVICE_IS_OFF << std::endl;

    }

}

void    indie::Gfx::clear() {
    this->_driver->beginScene(true, true, SBlack);
}

void    indie::Gfx::set_window_settings() {

    // Hide Cursor
    this->_device->getCursorControl()->setVisible(false);

    // Load Default Font
    this->loadFonts();

    // Set Event Receiver
    // this->_device->setEventReceiver(&this->_eventsOverlay);

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

void    indie::Gfx::test_drawing_map() {

    std::vector<std::pair<std::string, std::string> > tmp = {
                        std::make_pair("Map/bot_right.obj", "Map/bot_right.png"),
                        std::make_pair("Map/bot_left.obj", "Map/bot_left.png"),
                        std::make_pair("Map/top_left.obj", "Map/top_left.png"),
                        std::make_pair("Map/top_right.obj", "Map/top_right.png"),
                        std::make_pair("Map/pillars.obj", "Map/pillars.png"),
                        std::make_pair("Map/ground.obj", "Map/ground.png")
    };

    std::unique_ptr<indie::IScene>  mys = std::make_unique<Scene>(tmp, "Textures/Dome/Storm.jpg", -13.0f, 0.0f, 13.5f);
    
    std::vector<std::unique_ptr<indie::IScene> >    scenes;

    scenes.push_back(std::move(mys));

    this->loadScenes(std::move(scenes));

}