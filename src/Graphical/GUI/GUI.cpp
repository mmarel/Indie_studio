#include "Common/GUI.hpp"

indie::GUI::GUI(indie::Settings& settings, indie::GameState& state) : _posBackground(0), _settings(settings), _gameState(state), _components(), _loadComps(), _compActions() {

    _loadComps[indie::GameState::MAIN_MENU] = [this](){return loadMenu();};
    _loadComps[indie::GameState::SETTINGS] = [this](){return loadSettings();};
    _loadComps[indie::GameState::SCOREBOARD] = [this](){return loadScore();};
    _loadComps[indie::GameState::ROOM] = [this](){return loadRoom();};

}

std::size_t indie::GUI::size() const {
    return (_components.size());
}

indie::IComponent & indie::GUI::at(std::size_t n) const {
    return (*_components.at(n));
}

void indie::GUI::loadComponents(indie::GameState& state) {
    if (_loadComps.find(state) != _loadComps.end())
        _components = _loadComps[state]();
}

std::unique_ptr<std::vector<std::unique_ptr<indie::ISprite> > > indie::GUI::getSprites() const {
    std::unique_ptr<std::vector<std::unique_ptr<indie::ISprite> > > sprites;

    sprites = std::make_unique<std::vector<std::unique_ptr<indie::ISprite> > >();
    (*sprites).push_back(std::make_unique<indie::Sprite>("Menu/main/main_select_play.png", "Menu/main/main_select_settings.png", "Menu/main/main_select_highscores.png", "Menu/main/main_select_exit.png"));
    (*sprites).push_back(std::make_unique<indie::Sprite>("Menu/settings/settings_base.png"));
    (*sprites).push_back(std::make_unique<indie::Sprite>("Menu/room/room_base.png"));
    return (std::move(sprites));
}
void indie::GUI::notifyEvent(const indie::Event &event) {
    if (event.type == indie::EventType::ET_KEYBOARD)
        if (_compActions.find(event.kb_key) != _compActions.end())
            _compActions[event.kb_key]();
}

std::vector<std::unique_ptr<indie::IComponent>> indie::GUI::loadMenu() {
    std::vector<std::unique_ptr<indie::IComponent>> res;

    _posBackground = 0;
    ///Load menu components
    res.push_back(createComponent(0, 0.0f, 0.0f, 1.0f, 1.0f, indie::Color::White, indie::Color::White,
                                   "Bomberman", "Menu/main/main_select_play.png", "Menu/main/main_select_settings.png", "Menu/main/main_select_highscores.png", "Menu/main/main_select_exit.png"));
//    res.push_back(createComponent(1, 0.4f, 0.4f, 0.16f, 0.15f, indie::Color::White, indie::Color::White,
//                                  "Play", "Sprites/playButton.png", "Sprites/playButton2.png"));
//    res.push_back(createComponent(2, 0.33f, 0.6f, 0.3f, 0.1f, indie::Color::White, indie::Color::White,
//                                  "Settings", "Sprites/SettingsButton.png", "Sprites/SettingsButton2.png"));
//    res.push_back(createComponent(3, 0.4f, 0.8f, 0.15f, 0.1f, indie::Color::White, indie::Color::White,
//                                  "Exit", "Sprites/exitButton.png", "Sprites/exitButton2.png"));

    if (!_compActions.empty())
        _compActions.clear();

    _compActions[indie::KeyboardKey::KB_ARROW_DOWN] = [this](){mainMenuKeyDown();};
    _compActions[indie::KeyboardKey::KB_ARROW_UP] = [this](){mainMenuKeyUp();};
    _compActions[indie::KeyboardKey::KB_ARROW_RIGHT] = [this](){mainMenuKeyRight();};
    _compActions[indie::KeyboardKey::KB_ENTER] = [this](){mainMenuKeyEnter();};

    return (res);
}

std::vector<std::unique_ptr<indie::IComponent>> indie::GUI::loadSettings() {
    std::vector<std::unique_ptr<indie::IComponent>> res;

    ///Load Settings components

    if (!_compActions.empty())
        _compActions.clear();

    _compActions[indie::KeyboardKey::KB_ARROW_DOWN] = [this](){settMenuKeyDown();};
    _compActions[indie::KeyboardKey::KB_ARROW_UP] = [this](){settMenuKeyUp();};
    _compActions[indie::KeyboardKey::KB_ARROW_RIGHT] = [this](){settMenuKeyRight();};
    _compActions[indie::KeyboardKey::KB_ARROW_LEFT] = [this](){settMenuKeyLeft();};
    _compActions[indie::KeyboardKey::KB_ENTER] = [this](){settMenuKeyEnter();};

    return (res);
}

std::vector<std::unique_ptr<indie::IComponent>> indie::GUI::loadRoom() {
    std::vector<std::unique_ptr<indie::IComponent>> res;

    ///Load Room Components

    if (!_compActions.empty())
        _compActions.clear();

    _compActions[indie::KeyboardKey::KB_ARROW_DOWN] = [this](){roomMenuKeyDown();};
    _compActions[indie::KeyboardKey::KB_ARROW_UP] = [this](){roomMenuKeyUp();};
    _compActions[indie::KeyboardKey::KB_ARROW_RIGHT] = [this](){roomMenuKeyRight();};
    _compActions[indie::KeyboardKey::KB_ARROW_LEFT] = [this](){roomMenuKeyLeft();};
    _compActions[indie::KeyboardKey::KB_ENTER] = [this](){roomMenuKeyEnter();};

    return (res);
}

std::vector<std::unique_ptr<indie::IComponent>> indie::GUI::loadScore() {
    std::vector<std::unique_ptr<indie::IComponent>> res;

    ///Load Score components

    return (res);
}


///     Event Main Menu functions --- Start

void indie::GUI::mainMenuKeyDown() {
    std::cout << "POS : " << _components.at(0)->getBackgroundPos() << std::endl;
    std::cout << "POS 2 : " << _posBackground << std::endl;
    if (_posBackground + 1 < 4)
    {
//        std::cout << "SET : " << _posBackground + 1 << std::endl;
        _components.at(0)->setBackgroundPos(++_posBackground);
    }
}

void indie::GUI::mainMenuKeyUp() {
    std::cout << "POS : " << _components.at(0)->getBackgroundPos() << std::endl;
    std::cout << "POS 2 : " << _posBackground << std::endl;

    if (_posBackground > 0)
        _components.at(0)->setBackgroundPos(--_posBackground);
}

void indie::GUI::mainMenuKeyRight() {
//    if (_compId == 1)
//        loadComponents(indie::GameState::ROOM);
//    if (_compId == 2)
//        loadComponents(indie::GameState::SETTINGS);
}

void indie::GUI::mainMenuKeyEnter() {
//    if (_compId == 1)
//        loadComponents(indie::GameState::ROOM);
//    if (_compId == 2)
//        loadComponents(indie::GameState::SETTINGS);
}

///     Event Main Menu functions --- End
///---------------------------------------------------------
///     Event Settings Menu functions --- Start

void indie::GUI::settMenuKeyDown() {
//    if (_compId + 1 < _components.size())
//    {
//        for (size_t i = 1; i < _components.size(); ++i)
//        {
//            if (i == _compId + 1)
//                _components.at(i)->setBackgroundPos(1);
//            else
//                _components.at(i)->setBackgroundPos(0);
//        }
//        _compId++;
//    }
}

void indie::GUI::settMenuKeyUp() {
//    if (_compId - 1 > 1)
//    {
//        for (size_t i = 1; i < _components.size(); ++i)
//        {
//            if (i == _compId - 1)
//                _components.at(i)->setBackgroundPos(1);
//            else
//                _components.at(i)->setBackgroundPos(0);
//        }
//        _compId--;
//    }
}

void indie::GUI::settMenuKeyRight() {
//    switch (_compId) {
//        case 1 :{
////            if (_settings.volume + 1 < 99)
////                _settings.volume += 1;
//            break;
//        }
//        case 3:{
////            if (_settings.difficulty + 1 < 3)
////                _settings.difficulty += 1;
//            break;
//        }
//        case 4: loadComponents(indie::GameState::MAIN_MENU);
//            break;
//        default:
//            break;
//    }
}

void indie::GUI::settMenuKeyLeft() {
//    switch (_compId)
//    {
//        case 1 : {
//            if (_settings.volume - 1 > 0)
//                _settings.volume -= 1;
//            break;
//        }
//        case 3: {
////            if (_settings.difficulty  - 1 > -1)
////                _settings.difficulty -= 1;
//            break;
//        }
//        default:
//            break;
//    }
}

void indie::GUI::settMenuKeyEnter() {
//    if (_compId == 4)
//        loadComponents(indie::GameState::MAIN_MENU);
}

///     Event Settings Menu functions --- End
///---------------------------------------------------------
///     Event Room Menu functions --- Start

void indie::GUI::roomMenuKeyDown() {
//    if (_compId + 1 < _components.size())
//    {
//        for (size_t i = 1; i < _components.size(); ++i)
//        {
//            if (i == _compId + 1)
//                _components.at(i)->setBackgroundPos(1);
//            else
//                _components.at(i)->setBackgroundPos(0);
//        }
//        _compId++;
//    }
}

void indie::GUI::roomMenuKeyUp() {
//    if (_compId - 1 > 1)
//    {
//        for (size_t i = 1; i < _components.size(); ++i)
//        {
//            if (i == _compId - 1)
//                _components.at(i)->setBackgroundPos(1);
//            else
//                _components.at(i)->setBackgroundPos(0);
//        }
//        _compId--;
//    }
}

void indie::GUI::roomMenuKeyRight() {
//    switch (_compId) {
//        case 2: {
//            if (_settings.nplayers + 1 < 5)
//                _settings.nplayers++;
//            break;
//        }
//        case 3: {
//            if (_settings.nplayers + 1 < 5)
//                _settings.nplayers++;
//            break;
//        }
//        case 4: loadComponents(indie::GameState::INGAME);
//            break;
//        case 6: ///Join Component
//            break;
//        case 7: ///Host Component
//            break;
//        case 8: loadComponents(indie::GameState::MAIN_MENU);
//            break;
//        default:
//            break;
//    }
}

void indie::GUI::roomMenuKeyLeft() {
//    switch (_compId) {
//        case 2 : {
//            if (_settings.nplayers - 1 > 2)
//                _settings.nplayers--;
//            break;
//        }
//        case 3: {
//            if (_settings.nplayers - 1 > 2)
//                _settings.nplayers--;
//            break;
//        }
//        case 8: loadComponents(indie::GameState::MAIN_MENU);
//            break;
//        default:
//            break;
//    }
}

void indie::GUI::roomMenuKeyEnter() {
//    switch (_compId) {
//        case 2: {
//            if (_settings.nplayers + 1 < 5)
//                _settings.nplayers++;
//            break;
//        }
//        case 3: {
//            if (_settings.nplayers + 1 < 5)
//                _settings.nplayers++;
//            break;
//        }
//        case 4: loadComponents(indie::GameState::INGAME);
//            break;
//        case 6: ///Join Component
//            break;
//        case 7: ///Host Component
//            break;
//        case 8: loadComponents(indie::GameState::MAIN_MENU);
//            break;
//        default:
//            break;
//    }
}

///     Event Room Menu functions --- End
