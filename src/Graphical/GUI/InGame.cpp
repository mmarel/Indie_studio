#include "Common/GUI.hpp"

std::vector<std::unique_ptr<indie::IComponent>> indie::GUI::loadGuiGame() {
    std::vector<std::unique_ptr<indie::IComponent>> res;

    _posBackground = 0;
    size_t  nb_players = 1;

//bleu, rouge, jaune, vert
    while (nb_players <= _settings.nPlayers + _settings.nAIs)
    {
        switch (nb_players)
        {
            case 1: {
                res.push_back(createComponent(SpriteId::PLAYER_ICON, 0.025f, 0.025f, 0.125f, 0.125f, indie::Color::White, indie::Color::White));
                break;
            }
            case 2: {
                res.push_back(createComponent(SpriteId::PLAYER_ICON, 0.875f, 0.025f, 0.975f, 0.125f, indie::Color::White, indie::Color::White));
                res.at(res.size() - 1)->setBackgroundPos(1);
                break;
            }
            case 3: {
                res.push_back(createComponent(SpriteId::PLAYER_ICON, 0.025f, 0.875f, 0.125f, 0.975f, indie::Color::White, indie::Color::White));
                res.at(res.size() - 1)->setBackgroundPos(2);
                break;
            }
            case 4: {
                res.push_back(createComponent(SpriteId::PLAYER_ICON, 0.875f, 0.875f, 0.975f, 0.975f, indie::Color::White, indie::Color::White));
                res.at(res.size() - 1)->setBackgroundPos(3);
                break;
            }
            default:
                break;
        }
        ++nb_players;
    }
    return (res);
}

std::vector<std::unique_ptr<indie::IComponent>> indie::GUI::loadEndGame() {
    std::vector<std::unique_ptr<indie::IComponent>> res;
    std::unique_ptr<indie::Score> score = std::make_unique<indie::Score>();

    ///Load end game Components
    int _winner = 0;
    int _score  = 0;

    for (std::vector<std::unique_ptr<indie::Player>>::const_iterator i = _settings.players.begin(); i != _settings.players.end(); ++i)
    {
        if ((*i)->isAlive())
        {
            _score = (*i)->getScore();
            break;
        }
        _winner++;
    }


    res.push_back(createComponent(SpriteId::INGAME_MENU1, 0.0f, 0.0f, 1.0f, 1.0f, indie::Color::White, indie::Color::White));
    switch (_winner)
    {
        case 0: {
            res.push_back(createComponent(SpriteId::ENDGAME_MENU, 0.24f, 0.04f, 0.75f, 0.91f, indie::Color::White, indie::Color::White));
            res.at(0)->setBackgroundPos(0);
            break;
        }
        case 1: {
            res.push_back(createComponent(SpriteId::ENDGAME_MENU, 0.24f, 0.04f, 0.75f, 0.91f, indie::Color::White, indie::Color::White));
            res.at(res.size() - 1)->setBackgroundPos(1);
            break;
        }
        case 2: {
            res.push_back(createComponent(SpriteId::ENDGAME_MENU, 0.24f, 0.04f, 0.75f, 0.91f, indie::Color::White, indie::Color::White));
            res.at(res.size() - 1)->setBackgroundPos(2);
            break;
        }
        case 3: {
            res.push_back(createComponent(SpriteId::ENDGAME_MENU, 0.24f, 0.04f, 0.75f, 0.91f, indie::Color::White, indie::Color::White));
            res.at(res.size() - 1)->setBackgroundPos(3);
            break;
        }
        default:
            break;
    }
    getTabNumber(res, std::to_string(_score), 0.4f, 0.65f, 0.45f, 0.70f, 0.05f);
    score->add_score(_score);

    if (!_compActions.empty())
        _compActions.clear();

    _compActions[indie::KeyboardKey::KB_ENTER] = [this](){endGameMenuKeyEnter();};

    return (res);
}

void    indie::GUI::update_dead()
{
    for (size_t i = 0; i < _settings.players.size(); ++i)
    {
        if (_settings.players.at(i)->isAlive())
            _components.at(i)->setBackgroundPos(4);
    }
}

void    indie::GUI::endGameMenuKeyEnter()
{
    _gameState = indie::GameState::MAIN_MENU;
    loadComponents(_gameState);
}