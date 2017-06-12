#include "Common/GUI.hpp"

indie::GUI::GUI() : _components(), _loadComps() {

    _loadComps[indie::GameState::MENU] = std::bind(&indie::GUI::loadMenu, this);
    _loadComps[indie::GameState::SETTINGS] = std::bind(&indie::GUI::loadSettings, this);
    _loadComps[indie::GameState::SCORE] = std::bind(&indie::GUI::loadScore, this);
    _loadComps[indie::GameState::ROOM] = std::bind(&indie::GUI::loadRoom, this);
}

std::size_t indie::GUI::size() const {
    return (_components.size());
}

indie::IComponent & indie::GUI::at(std::size_t n) {
    return (*_components.at(n));
}

void indie::GUI::loadComponents(indie::GameState state) {
    if (_loadComps.find(state) != _loadComps.end())
        _components = _loadComps[state]();
}

std::vector<std::unique_ptr<indie::IComponent>> indie::GUI::loadMenu() {
    std::vector<std::unique_ptr<indie::IComponent>> res;

    ///Load menu components
    res.push_back(createComponent(0, 0, 0, 814, 134, indie::Color::Transparent, indie::Color::Red,
                                   "Bomberman", "Sprites/bombTitle.png"));
    res.push_back(createComponent(1, 0, 0, 180, 107, indie::Color::Transparent, indie::Color::White,
                                  "Play", "Sprites/playButton.png", "Sprites/playButton2.png"));
    res.push_back(createComponent(2, 0, 0, 323, 92, indie::Color::Transparent, indie::Color::White,
                                  "Settings", "Sprites/SettignsButton.png", "Sprites/SettingsButton2.png"));
    res.push_back(createComponent(3, 0, 0, 174, 85, indie::Color::Transparent, indie::Color::White,
                                  "Exit", "Sprites/exitButton.png", "Sprites/exitButton2.png"));

    return (res);
}

std::vector<std::unique_ptr<indie::IComponent>> indie::GUI::loadSettings() {
    std::vector<std::unique_ptr<indie::IComponent>> res;

    ///Load Settings components

    return (res);
}

std::vector<std::unique_ptr<indie::IComponent>> indie::GUI::loadScore() {
    std::vector<std::unique_ptr<indie::IComponent>> res;

    ///Load Score components

    return (res);
}

std::vector<std::unique_ptr<indie::IComponent>> indie::GUI::loadRoom() {
    std::vector<std::unique_ptr<indie::IComponent>> res;

    ///Load Room Components

    return (res);
}

std::vector<std::unique_ptr<indie::ISprite> > indie::GUI::getSprites() {
    std::vector<std::unique_ptr<indie::ISprite> > res;
    std::unique_ptr<indie::ISprite> val;
    indie::ISprite  *tmp_sprite;

    for (size_t i = 0; i < _components.size(); ++i)
    {
        tmp_sprite = _components.at(i)->getSprite();
        val = std::make_unique<indie::Sprite>();
        std::cout << "ICI : " << tmp_sprite->SpritesCount() << std::endl;
        for (size_t j = 0; j < tmp_sprite->SpritesCount(); ++j) {
            std::cout << "ICI (second loop)\n";
            val->addPath(tmp_sprite->getGraphicPath(j));
        }
        res.push_back(std::move(val));
    }
    return (res);
}