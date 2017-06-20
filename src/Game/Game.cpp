#include "Game/Game.hpp"

indie::Game::Game() :
  _players(),
  _soundsToPlay(),
  _music(indie::Sound(indie::SoundId::SOUND_NONE, indie::SoundAction::PLAY, 50.0f)),
  _gameState(SPLASH_SCREEN),
  _events(),
  _map(),
  _settings(),
  _gui(_settings, _gameState),
  _objectsStates()
 {
 }

indie::Game::~Game() {}

indie::GameState indie::Game::getGameState() const {
  return _gameState;
}

void indie::Game::notifyEvent(std::vector<Event> &&events) {
  _events.insert(_events.end(), events.begin(), events.end());
}

const std::vector<size_t> &indie::Game::getObjectsId() const {
  return _map.getObjectsId();
}

const std::vector<indie::Sound> &indie::Game::getSoundsToPlay() const {
  /*const std::vector<indie::Souns> &gui_sounds = _gui.getSoundsToPlay(); TODO add gui sounds
  _soundsToPlay.inset(_soundsToPlay.begin(), gui_sound.begin()), gui_sounds.end());
   if (_gui.hasVolumeChanged()) {
   _music.mode = indie::Sound::VOLUME;
    _music.volume = _settings.volume;
    _soundsToPlay.push_back(_music);
  }*/
  return _soundsToPlay;
}

const indie::IMap &indie::Game::getCurrentMap() const {
  return _map;
}

const indie::IGUI &indie::Game::getCurrentGUI() const {
  return _gui;
}

void indie::Game::setObjectsAnimationState(const std::vector<indie::AnimationState> &objectsStates) {
  _objectsStates = objectsStates;
  //_objectsStates.insert(_objectsStates.end(), objectsStates.begin(), objectsStates.end());
}

indie::Player &indie::Game::getPlayerById(size_t playerId) {
  return *(std::find_if(_players.begin(), _players.end(),
            [&playerId](Player &player) {
              return player.getId() == playerId;
            }));
}

bool indie::Game::isEnded() const {
  //int nPlayers = 0;
  return false;
  std::cout << "end game\n";
  return true;
  /*nPlayers = std::accumulate(_settings.players.begin(), _settings.players.end(), 0,
              [](Player &player) {
                return
              });*/
}

void indie::Game::reset() {
  _players.clear();
  _music = indie::Sound(indie::SoundId::SOUND_NONE, indie::SoundAction::PLAY, 50.0f);
  _events.clear();
  _map.clear();
  _settings = Settings();
  _objectsStates.clear();
}

void indie::Game::start() {
  std::cout << "start game\n";
  for (size_t i = 1; i <= 2; i++) {
    _players.push_back(indie::Player(i));
  }
  return;
  reset();
  _settings.nPlayers = 2;
  //_soundsToPlay.push_back(indie::Sound(indie::SoundId::SOUND_SKELELETON_SPAWN, indie::SoundAction::UNIQUE, 50.0f));
  for (size_t i = 1; i <= _settings.nPlayers; i++) {
    _players.push_back(indie::Player(i));
  }
  // TODO init AIs
  _map.init(0, _settings.nPlayers + _settings.nAIs);
}
