//
// Author: Sebastien Jacobin 
// Date: 2017-06-01 21:05:35 
//
// Last Modified by:   Sebastien Jacobin 
// Last Modified time: 2017-06-01 21:05:35
//

#include "Interfaces/GameState.hpp"

indie::EventKey::EventKey() {
    for (std::size_t i = 0; i < irr::KEY_KEY_CODES_COUNT; ++i)
        this->keyMap[i] = false;
}

bool indie::EventKey::OnEvent(const irr::SEvent &event) {
    if (event.EventType == irr::EET_KEY_INPUT_EVENT)
        this->keyMap[event.KeyInput.Key] = event.KeyInput.PressedDown;
    return (false);
}

bool indie::EventKey::IsKeyDown(irr::EKEY_CODE keyCode) const {
    return this->keyMap[keyCode];
}

int indie::EventKey::getKeyPressed() const {
    for (std::size_t i = 0; i < irr::KEY_KEY_CODES_COUNT; ++i) {
        if (this->keyMap[i])
            return (this->keyMap[i]);
    }
    return (0);
}

// void    indie::EventKey::emptyKeyMap() {

//     for (std::size_t i = 0; i < irr::KEY_KEY_CODES_COUNT; ++i) {
//         this->keyMap[i] = false;
//     }

// }