#include "Game/Game.hpp"


std::unique_ptr<std::vector<std::unique_ptr<indie::ISprite> > > indie::Game::getSpritesToLoad() const {
  std::unique_ptr<std::vector<std::unique_ptr<indie::ISprite> > >  spritesToLoad;

    spritesToLoad = std::make_unique<std::vector<std::unique_ptr<indie::ISprite> > >();
  /*spritesToLoad[indie::SpriteType::SPRT_BOMBTITLE] =
    std::make_unique<indie::Sprite>(std::vector<std::string>({"Sprites/bombTitle.png"}));
  spritesToLoad[indie::SpriteType::SPRT_EXITBUTTON] =
    std::make_unique<indie::Sprite>(std::vector<std::string>({"Sprites/exitButton.png", "Sprites/exitButton2.png"}));
  spritesToLoad[indie::SpriteType::SPRT_OPTBUTTON] =
  std::make_unique<indie::Sprite>(std::vector<std::string>({"Sprites/optionButton.png", "Sprites/optionButton2.png"}));
  spritesToLoad[indie::SpriteType::SPRT_PLAYBUTTON] =
  std::make_unique<indie::Sprite>(std::vector<std::string>({"Sprites/playButton.png", "Sprites/playButton2.png"}));
  spritesToLoad[indie::SpriteType::SPRT_SETTINGSBUTTON] =
  std::make_unique<indie::Sprite>(std::vector<std::string>({"Sprites/settingsButton.png", "Sprites/settingsButton2.png"}));*/
  return std::move(spritesToLoad);
}

std::unique_ptr<std::vector<std::unique_ptr<indie::IModel> > > indie::Game::getModelsToLoad() const {
  std::unique_ptr<std::vector<std::unique_ptr<indie::IModel> > > modelsToLoad;

  modelsToLoad = std::make_unique<std::vector<std::unique_ptr<indie::IModel> > >();
  (*modelsToLoad)[indie::ModelType::MODEL_SKELETON] =
    std::make_unique<indie::Model>("Models/SkeletonMage/SkeletonMage.b3d",
      std::vector<std::pair<size_t, size_t> >(
        {{1, 36}, {38, 68}, {70, 150}, {152, 175}, {177, 252}})
    );
  return std::move(modelsToLoad);
}

std::unique_ptr<std::vector<std::pair<std::string, indie::SoundType> > > indie::Game::getSoundsToLoad() const {
  std::unique_ptr<std::vector<std::pair<std::string, indie::SoundType> > > soundsToLoad;

  return std::move(soundsToLoad);
}

std::unique_ptr<std::vector<std::unique_ptr<indie::IScene> > > indie::Game::getScenesToLoad() const {
  std::unique_ptr<std::vector<std::unique_ptr<indie::IScene> > > scenesToLoad;

  return std::move(scenesToLoad);
}
