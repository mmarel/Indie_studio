 #include "Common/GUI.hpp"

indie::GUI::GUI() : _sprites(), _components(), _loadComps() {

    _loadComps[indie::GameState::MENU] = std::bind(&indie::GUI::loadMenu, this);
    _loadComps[indie::GameState::SETTINGS] = std::bind(&indie::GUI::loadSettings, this);
    _loadComps[indie::GameState::SCORE] = std::bind(&indie::GUI::loadScore, this);
    _loadComps[indie::GameState::ROOM] = std::bind(&indie::GUI::loadRoom, this);
}

std::size_t indie::GUI::size() const {
    return (_components.size());
}

indie::IComponent & indie::GUI::at(std::size_t n) const {
    return (*_components.at(n));
}

void indie::GUI::loadComponents(indie::GameState state) {
    if (_loadComps.find(state) != _loadComps.end())
        _components = _loadComps[state]();
}

std::vector<std::shared_ptr<indie::IComponent>> indie::GUI::loadMenu() {
    std::vector<std::shared_ptr<indie::IComponent>> res;

    ///Load menu components
    res.push_back(createComponent(0, 0.1f, 0.1f, 0.75f, 0.15f, indie::Color::White, indie::Color::Red,
                                   "Bomberman", "Sprites/bombTitle.png"));
    res.push_back(createComponent(1, 0.4f, 0.4f, 0.16f, 0.15f, indie::Color::White, indie::Color::White,
                                  "Play", "Sprites/playButton.png", "Sprites/playButton2.png"));
    res.push_back(createComponent(2, 0.33f, 0.6f, 0.3f, 0.1f, indie::Color::White, indie::Color::White,
                                  "Settings", "Sprites/SettingsButton.png", "Sprites/SettingsButton2.png"));
    res.push_back(createComponent(3, 0.4f, 0.8f, 0.15f, 0.1f, indie::Color::White, indie::Color::White,
                                  "Exit", "Sprites/exitButton.png", "Sprites/exitButton2.png"));

    return (res);
}

std::vector<std::shared_ptr<indie::IComponent>> indie::GUI::loadSettings() {
    std::vector<std::shared_ptr<indie::IComponent>> res;

    ///Load Settings components

    return (res);
}

std::vector<std::shared_ptr<indie::IComponent>> indie::GUI::loadScore() {
    std::vector<std::shared_ptr<indie::IComponent>> res;

    ///Load Score components

    return (res);
}

std::vector<std::shared_ptr<indie::IComponent>> indie::GUI::loadRoom() {
    std::vector<std::shared_ptr<indie::IComponent>> res;

    ///Load Room Components

    return (res);
}

std::vector<std::shared_ptr<indie::ISprite> > indie::GUI::getSprites() {
    return (_sprites);
}
