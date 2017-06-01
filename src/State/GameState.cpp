#include "Interfaces/GameState.hpp"

indie::EventKey::EventKey() {
    for (int i = 0; i < irr::KEY_KEY_CODES_COUNT; ++i)
        KeyIsDown[i] = false;
}

bool indie::EventKey::OnEvent(const irr::SEvent &event) {
    if (event.EventType == irr::EET_KEY_INPUT_EVENT)
        KeyIsDown[event.KeyInput.Key] = event.KeyInput.PressedDown;
    return (false);
}

bool indie::EventKey::IsKeyDown(irr::EKEY_CODE keyCode) const {
    return KeyIsDown[keyCode];
}

int indie::EventKey::getKeyPressed() const {
    for (int i = 0; i < irr::KEY_KEY_CODES_COUNT; ++i) {
        if (KeyIsDown[i])
            return (KeyIsDown[i]);
    }
    return (0);
}