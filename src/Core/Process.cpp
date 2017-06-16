//
// Author: Marwane Khsime 
// Date: 2017-06-12 21:25:47 
//
// Last Modified by:   Marwane Khsime 
// Last Modified time: 2017-06-12 21:25:47
//

#include "Core/Core.hpp"

void        indie::Core::process() {

    // Notify the game by sending gfx inputs
    this->notifyGame();

    // Run the Game once time
    this->_game->process();

    std::cout << "GAME PROCCESS OK" << std::endl;

    this->_gfx->updateMap(this->_game->getCurrentMap());
    std::cout << "GFX MAP OK" << std::endl;

    //this->_gfx->updateGUI(this->_game->getCurrentGUI());
    std::cout << "GFX GUI OK" << std::endl;

    this->_gfx->display();

    // std::this_thread::sleep_for(std::chrono::milliseconds(100));
    std::cout << "turn" << std::endl;
}