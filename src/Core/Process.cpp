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

    this->_gfx->updateMap(this->_game->getCurrentMap());
    this->_gfx->updateGUI(this->_game->getCurrentGUI());

    this->_gfx->display();

    std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    std::cout << "turn" << std::endl;
}