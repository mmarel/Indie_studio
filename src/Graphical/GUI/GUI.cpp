#include <Game/Score.hpp>
#include <Interfaces/Sound.hpp>
#include "Common/GUI.hpp"

indie::GUI::GUI(indie::Settings& settings, indie::GameState& state) : _posBackground(0), _nbPlayersH(0), _nbPlayersAI(0), _settings(settings), _gameState(state), _components(), _loadComps(), _compActions() {

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
    if (!_components.empty())
        _components.clear();
    if (_loadComps.find(state) != _loadComps.end())
        _components = _loadComps[state]();
}

std::unique_ptr<std::vector<std::unique_ptr<indie::ISprite> > > indie::GUI::getSprites() const {
    std::unique_ptr<std::vector<std::unique_ptr<indie::ISprite> > > sprites;

    sprites = std::make_unique<std::vector<std::unique_ptr<indie::ISprite> > >();
    (*sprites).push_back(std::make_unique<indie::Sprite>("Menu_final/MAIN/base.png"));
    (*sprites).push_back(std::make_unique<indie::Sprite>("Menu_final/arrow.png", "Menu_final/arrow-rev.png",
                                                         "Menu_final/arrow-down.png", "Menu_final/arrow-upleft.png"));
    (*sprites).push_back(std::make_unique<indie::Sprite>("Menu_final/SETTINGS/base.png"));
    (*sprites).push_back(std::make_unique<indie::Sprite>("Menu_final/SETTINGS/sound_0.png",
                                                         "Menu_final/SETTINGS/sound_1.png",
                                                         "Menu_final/SETTINGS/sound_2.png",
                                                         "Menu_final/SETTINGS/sound_3.png",
                                                         "Menu_final/SETTINGS/sound_4.png",
                                                         "Menu_final/SETTINGS/sound_5.png",
                                                         "Menu_final/SETTINGS/sound_6.png",
                                                         "Menu_final/SETTINGS/sound_7.png",
                                                         "Menu_final/SETTINGS/sound_8.png",
                                                         "Menu_final/SETTINGS/sound_9.png",
                                                         "Menu_final/SETTINGS/sound_10.png"));
    (*sprites).push_back(std::make_unique<indie::Sprite>("Menu_final/SETTINGS/AI_normal.png",
                                                         "Menu_final/SETTINGS/AI_hard.png"));
    (*sprites).push_back(std::make_unique<indie::Sprite>("Menu_final/ROOM/room_base.png"));
    (*sprites).push_back(std::make_unique<indie::Sprite>("Sprites/score.png"));
    (*sprites).push_back(std::make_unique<indie::Sprite>("Menu_final/NUMBERS/0.png",
                                                         "Menu_final/NUMBERS/1.png",
                                                         "Menu_final/NUMBERS/2.png",
                                                         "Menu_final/NUMBERS/3.png",
                                                         "Menu_final/NUMBERS/4.png",
                                                         "Menu_final/NUMBERS/5.png",
                                                         "Menu_final/NUMBERS/6.png",
                                                         "Menu_final/NUMBERS/7.png",
                                                         "Menu_final/NUMBERS/8.png",
                                                         "Menu_final/NUMBERS/9.png"));
    return (std::move(sprites));
}

void indie::GUI::notifyEvent(const indie::Event &event) {
    if (event.type == indie::EventType::ET_KEYBOARD)
    {
        if (_compActions.find(event.kb_key) != _compActions.end())
            _compActions[event.kb_key]();
    }
}

std::vector<std::unique_ptr<indie::IComponent>> indie::GUI::loadMenu() {
    std::vector<std::unique_ptr<indie::IComponent>> res;

    _posBackground = 0;
    ///Load menu components
     res.push_back(createComponent(0, 0.0f, 0.0f, 1.0f, 1.0f, indie::Color::White, indie::Color::White));
     res.push_back(createComponent(1, 0.31f, 0.35f, 0.36f, 0.417f, indie::Color::White, indie::Color::White));

    ///Load Menu Events
    if (!_compActions.empty())
        _compActions.clear();

    _compActions[indie::KeyboardKey::KB_ARROW_DOWN] = [this](){mainMenuKeyDown();};
    _compActions[indie::KeyboardKey::KB_ARROW_UP] = [this](){mainMenuKeyUp();};
    _compActions[indie::KeyboardKey::KB_ARROW_RIGHT] = [this](){mainMenuKeyAccess();};
    _compActions[indie::KeyboardKey::KB_ENTER] = [this](){mainMenuKeyAccess();};

    return (res);
}

std::vector<std::unique_ptr<indie::IComponent>> indie::GUI::loadSettings() {
    std::vector<std::unique_ptr<indie::IComponent>> res;

    ///Load Settings components
    _posBackground = 0;

    res.push_back(createComponent(2, 0.0f, 0.0f, 1.0f, 1.0f, indie::Color::White, indie::Color::White));
    res.push_back(createComponent(1, 0.57f, 0.3f, 0.61f, 0.37f, indie::Color::White, indie::Color::White));
    res.push_back(createComponent(3, 0.54f, 0.39f, 0.76f, 0.47f, indie::Color::White, indie::Color::White));
    res.push_back(createComponent(4, 0.54f, 0.58f, 0.76f, 0.75f, indie::Color::White, indie::Color::White));

    ///Load Settings Values
    res.at(2)->setBackgroundPos(static_cast<size_t>(_settings.volume / 10));
    res.at(3)->setBackgroundPos(static_cast<size_t >(_settings.difficulty));

    ///Load Settings Events
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

    _nbPlayersH = 1;
    _nbPlayersAI = 1;
    res.push_back(createComponent(5, 0.0f, 0.0f, 1.0f, 1.0f, indie::Color::White, indie::Color::White));
    res.push_back(createComponent(1, 0.53f, 0.35f, 0.57f, 0.4f, indie::Color::White, indie::Color::White));
    res.push_back(createComponent(7, 0.63f, 0.36f, 0.66f, 0.39f, indie::Color::White, indie::Color::White));
    res.push_back(createComponent(7, 0.63f, 0.4f, 0.66f, 0.43f, indie::Color::White, indie::Color::White));

    res.at(2)->setBackgroundPos(_nbPlayersH);
    res.at(3)->setBackgroundPos(_nbPlayersAI);

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
    std::unique_ptr<indie::Score> score = std::make_unique<indie::Score>();
    double  y;
    double  height;

    _posBackground = 0;

    ///Load Score components


    std::vector<int> scores = score->GetScores();
    std::vector<std::string> dates = score->GetDates();

    res.push_back(createComponent(6, 0.0f, 0.0f, 1.0f, 1.0f, indie::Color::White, indie::Color::White));
    y = 0.35f;
    height = 0.41f;
    for(std::vector<int>::iterator i = scores.begin(); i != scores.end(); ++i)  
    {
        getTabNumber(res, std::to_string(*i), 0.10f, y, 0.16f, height);
        y += 0.1;
        height += 0.1;
    }
    y = 0.35f;
    height = 0.41f;
    for(std::vector<std::string>::iterator i = dates.begin(); i != dates.end();++i)
    {
        getTabDates(res, *i, 0.33f, y, 0.39f, height);
        y += 0.1;
        height += 0.1;
    }

    if (!_compActions.empty())
        _compActions.clear();

    _compActions[indie::KeyboardKey::KB_ENTER] = [this](){scoreMenuKeyEnter();};

    return (res);
}


///     Event Main Menu functions --- Start

void indie::GUI::mainMenuKeyDown() {
    switch (_posBackground)
    {
        case 0: _components.at(1)->setPos(0.29f, 0.435f, 0.34f, 0.505f);
            break;
        case 1: _components.at(1)->setPos(0.27f, 0.515f, 0.32f, 0.58f);
            break;
        case 2: _components.at(1)->setPos(0.31f, 0.6f, 0.36f, 0.67f);
            break;
        default:
            break;
    }
    if (_posBackground + 1 < 4)
        ++_posBackground;
}

void indie::GUI::mainMenuKeyUp() {
    switch (_posBackground)
    {
        case 1: _components.at(1)->setPos(0.31f, 0.35f, 0.36f, 0.417f);
            break;
        case 2: _components.at(1)->setPos(0.29f, 0.435f, 0.34f, 0.505f);
            break;
        case 3: _components.at(1)->setPos(0.27f, 0.515f, 0.32f, 0.58f);
            break;
        default:
            break;
    }
    if (_posBackground > 0)
        --_posBackground;
}

void indie::GUI::mainMenuKeyAccess(){
    switch (_posBackground)

    {
        case 0: loadComponents((_gameState = indie::GameState::ROOM));
            break;
        case 1: loadComponents((_gameState = indie::GameState::SETTINGS));
            break;
        case 2: loadComponents((_gameState = indie::GameState::SCOREBOARD));
            break;
        case 3: loadComponents((_gameState = indie::GameState::QUIT));
            break;
        default:
            break;
    }
}

///     Event Main Menu functions --- End

///---------------------------------------------------------

///     Event Settings Menu functions --- Start

void indie::GUI::settMenuKeyDown() {
    switch (_posBackground)
    {
        case 0: _components.at(1)->setPos(0.57f, 0.47f, 0.61f, 0.53f);
            break;
        case 1: {
            _components.at(1)->setPos(0.53f, 0.77f, 0.58f, 0.82f);
            _components.at(1)->setBackgroundPos(2);
            break;
        }
        default:
            break;
    }
    if (_posBackground + 1 < 3)
        ++_posBackground;
}

void indie::GUI::settMenuKeyUp() {
    switch (_posBackground)
    {
        case 1: {
            _components.at(1)->setPos(0.57f, 0.3f, 0.61f, 0.37f);
            _components.at(1)->setBackgroundPos(0);
            break;
        }
        case 2: {
            _components.at(1)->setPos(0.57f, 0.47f, 0.61f, 0.53f);
            _components.at(1)->setBackgroundPos(0);
            break;
        }
        default:
            break;
    }
    if (_posBackground > 0)
        --_posBackground;
}

void indie::GUI::settMenuKeyRight() {
    switch (_posBackground) {
        case 0 :{
            if (_settings.volume + 10 <= 100) {
                _settings.volume += 10;
                _components.at(2)->setBackgroundPos(static_cast<size_t >(_settings.volume / 10));
            }
            break;
        }
        case 1:{
            if (_settings.difficulty == indie::IA_LEVEL::IA_MEDIUM) {
                _settings.difficulty = indie::IA_LEVEL::IA_HARD;
                _components.at(3)->setBackgroundPos(static_cast<size_t >(_settings.difficulty));
            }
            break;
        }
        case 2: loadComponents((_gameState = indie::GameState::MAIN_MENU));
            break;
        default:
            break;
    }
}

void indie::GUI::settMenuKeyLeft() {
    switch (_posBackground)
    {
        case 0 : {
            if (_settings.volume - 10 >= 0) {
                _settings.volume -= 10;
                _components.at(2)->setBackgroundPos(static_cast<size_t >(_settings.volume / 10));
            }
            break;
        }
        case 1: {
            if (_settings.difficulty == indie::IA_LEVEL::IA_HARD) {
                _settings.difficulty = indie::IA_LEVEL::IA_MEDIUM;
                _components.at(3)->setBackgroundPos(static_cast<size_t >(_settings.difficulty));
            }
            break;
        }
        default:
            break;
    }
}

void indie::GUI::settMenuKeyEnter() {
    if (_posBackground == 2)
        loadComponents((_gameState = indie::GameState::MAIN_MENU));
}

///     Event Settings Menu functions --- End

///---------------------------------------------------------

///     Event Room Menu functions --- Start

void indie::GUI::roomMenuKeyDown() {
    switch (_posBackground)
    {
        case 0: _components.at(1)->setPos(0.53f, 0.39f, 0.57f, 0.44f);
            break;
        case 1: {
            _components.at(1)->setPos(0.57f, 0.67f, 0.61f, 0.72f);
            _components.at(1)->setBackgroundPos(1);
            break;
        }
        case 2: {
            _components.at(1)->setPos(0.66f, 0.82f, 0.7f, 0.87f);
            _components.at(1)->setBackgroundPos(3);
            break;
        }
        default:
            break;
    }
    if (_posBackground + 1 < 4)
        ++_posBackground;
}

void indie::GUI::roomMenuKeyUp() {
    switch (_posBackground)
    {
        case 1: {
            _components.at(1)->setPos(0.53f, 0.35f, 0.57f, 0.4f);
            _components.at(1)->setBackgroundPos(0);
            break;
        }
        case 2: {
            _components.at(1)->setPos(0.53f, 0.39f, 0.57f, 0.44f);
            _components.at(1)->setBackgroundPos(0);
            break;
        }
        case 3: {
            _components.at(1)->setPos(0.57f, 0.67f, 0.61f, 0.72f);
            _components.at(1)->setBackgroundPos(1);
            break;
        }
        default:
            break;
    }
    if (_posBackground > 0)
        --_posBackground;
}

void indie::GUI::roomMenuKeyRight() {
    switch (_posBackground)
    {
        case 0: {
            if (_nbPlayersH + 1 < 3)
                _components.at(2)->setBackgroundPos(++_nbPlayersH);
            if (_nbPlayersH + _nbPlayersAI > 4)
                _components.at(3)->setBackgroundPos(--_nbPlayersAI);
            break;
        }
        case 1: {
            if ((_nbPlayersAI + 1) + _nbPlayersH < 5)
                _components.at(3)->setBackgroundPos(++_nbPlayersAI);
        }
        default:
            break;
    }
    _settings.nplayers = _nbPlayersH + _nbPlayersAI;
}

void indie::GUI::roomMenuKeyLeft() {
    switch (_posBackground)
    {
        case 0: {
            if (_nbPlayersH > 1)
                _components.at(2)->setBackgroundPos(--_nbPlayersH);
            if (_nbPlayersH && !_nbPlayersAI)
                _components.at(3)->setBackgroundPos(++_nbPlayersAI);
            break;
        }
        case 1: {
            if ((_nbPlayersAI + _nbPlayersH > _nbPlayersH))
                _components.at(3)->setBackgroundPos(--_nbPlayersAI);
            if (_nbPlayersH == 1)
                _components.at(3)->setBackgroundPos((_nbPlayersAI = 1));
            break;
        }
        default:
            break;
    }
    _settings.nplayers = _nbPlayersH + _nbPlayersAI;
}

void indie::GUI::roomMenuKeyEnter() {
    if (_posBackground == 2)
        loadComponents((_gameState = indie::GameState::MAIN_MENU));
    if (_posBackground == 3)
        loadComponents((_gameState = indie::GameState::INGAME));
}

///     Event Room Menu functions --- End
///---------------------------------------------------------
///     Event Score Menu functions --- Start

void indie::GUI::scoreMenuKeyEnter() {
    _gameState = indie::GameState::MAIN_MENU;
    loadComponents(_gameState);
}

void    indie::GUI::getTabNumber(std::vector<std::unique_ptr<indie::IComponent>> &res, std::string score, double x, double y, double width, double height)
{
    int nb;
    double  pos_x;

    pos_x = x;
    for (int i = 0; score[i] != '\0'; ++i)
    {
        nb = score[i] - 48 + 7;
        res.push_back(createComponent(nb, pos_x, y, width, height, indie::Color::White, indie::Color::White));
        pos_x += 0.06;
        width += 0.06;
    }
}

void    indie::GUI::getTabDates(std::vector<std::unique_ptr<indie::IComponent>> &res, std::string score, double x, double y, double width, double height)
{
    int nb;
    double  pos_x;

    pos_x = x;
    for (int i = 0; score[i] != '\0'; ++i)
    {
        if (score[i] >= '0' && score[i] <= '9')
            nb = score[i] - 48 + 7;             
        else
            nb = 17;
        res.push_back(createComponent(nb, pos_x, y, width, height, indie::Color::White, indie::Color::White));
        pos_x += 0.06;
        width += 0.06;
    }
}

///     Event Score Menu functions --- End
