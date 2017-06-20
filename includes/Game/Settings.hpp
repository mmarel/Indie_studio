#ifndef SETTINGS_HPP
# define SETTINGS_HPP

# include "Interfaces/Event.hpp"

namespace indie {

    typedef enum        e_PlayerType {
      PLAYER_UNKNOWN = -1,
      PLAYER_HUMAN,
      PLAYER_AI
    }                     PlayerType;

    typedef enum          e_IA_LEVEL {
      IA_UNKNOWN = -1,
      IA_MEDIUM,
      IA_HARD
    }                     IA_LEVEL;

    typedef enum          e_PLAY_MOD {
      PLAY_MODE_UNKNOWN = -1,
      PLAY_MODE_LOCAL,
      PLAY_MODE_ONLINE_HOST,
      PLAY_MODE_ONLINE_CLIENT
    }                     PlayMode;

    struct              Settings {
      float                     volume;
      IA_LEVEL                  difficulty;
      PlayMode                  mode;
      size_t                    nPlayers;
      size_t                    nAIs;
      Settings(float volume_ = 50.0f,
                IA_LEVEL difficulty_ = IA_LEVEL::IA_MEDIUM,
                PlayMode mode_ = PlayMode::PLAY_MODE_LOCAL,
                size_t nPlayers_ = 0, size_t nAIs_ = 0) :
        volume(volume_), difficulty(difficulty_), mode(mode_),
        nPlayers(nPlayers_), nAIs(nAIs_){}
    };
}


#endif // SETTINGS_HPP
