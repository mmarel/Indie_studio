#include "Game/Game.hpp"

indie::Game::Game() :
  _players(),
  _soundsToPlay(),
  _music(indie::Sound(indie::SoundId::SOUND_NONE, indie::SoundAction::PLAY, 50.0f)),
  _gameState(SPLASH_SCREEN),
  _events(),
  _map(),
  _settings(_players),
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

indie::Player &indie::Game::getBombOwner(size_t bombId) {
  std::vector<std::unique_ptr<indie::Player> >::iterator player_it;

  player_it = std::find_if(_players.begin(), _players.end(),
                [&bombId](std::unique_ptr<indie::Player> &player) {
                  return player->hasBomb(bombId);
                });
  return *(*player_it);
}

indie::Player &indie::Game::getPlayerById(size_t playerId) {
  std::vector<std::unique_ptr<indie::Player> >::iterator player_it;

  player_it = std::find_if(_players.begin(), _players.end(),
            [&playerId](std::unique_ptr<indie::Player> &player)-> bool {
              return player->getId() == playerId;
            });
  return *(*player_it);
}

bool indie::Game::isEnded() const {
  int nPlayers = 0;

  nPlayers =
    std::accumulate(_players.begin(), _players.end(), 0,
    [](int i, const std::unique_ptr<Player> &player)->int {
      return i + static_cast<int>(player->isAlive());
    });
  return nPlayers < 2;
}

void indie::Game::reset() {
  _players.clear();
  _music = indie::Sound(indie::SoundId::SOUND_NONE, indie::SoundAction::PLAY, 50.0f);
  _events.clear();
  _map.clear();
  _objectsStates.clear();
}

void indie::Game::start() {
  std::cout << "start game " << _settings.nPlayers << "players "<< _settings.nAIs << " ais\n";
  reset();
  _map.init(0, _settings.nPlayers/* + _settings.nAIs*/);
  //_soundsToPlay.push_back(indie::Sound(indie::SoundId::SOUND_SKELELETON_SPAWN, indie::SoundAction::UNIQUE, 50.0f));

  for (size_t i = 1; i <= _settings.nPlayers; i++) {
    std::cout << "add players " << i << "\n";
    _players.push_back(std::make_unique<indie::Player>(i, static_cast<indie::ELookAt>(i - 1)));
  }
  std::cout << "player 1 id " << _players[0]->getId() << std::endl;
  return;
  for (size_t i = 1; i <= _settings.nAIs; i++) {
    std::cout << "add ai " << i + 2 << "\n";
    _players.push_back(std::make_unique<indie::Player>(i,
                                    static_cast<indie::ELookAt>(_settings.nPlayers + i - 1),
                                    indie::PlayerType::PLAYER_AI, _settings.difficulty));
  }
}
