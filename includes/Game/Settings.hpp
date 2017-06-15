#ifndef SETTINGS_HPP
# define SETTINGS_HPP

# include "Interfaces/Event.hpp"

namespace indie {

    typedef enum    e_BonusType {
      BONUS_UNKNOWN = -1
    }               BonusType;

    typedef struct  s_Bonus {
      BonusType     type;
      size_t        duration;
    }               Bonus;

    typedef struct        s_Player {
      KeyboardKey         move_left;
      KeyboardKey         move_right;
      KeyboardKey         move_up;
      KeyboardKey         move_down;
      KeyboardKey         bomb;
      std::vector<Bonus>  bonus;
      size_t              id;
    } Player;

    typedef enum          e_IA_LEVEL {
      IA_UNKNOWN = -1,
      IA_EASY,
      IA_MEDIUM,
      IA_HARD
    }             IA_LEVEL;

    typedef struct              s_Settings {
      size_t                    volume;
      IA_LEVEL                  difficulty;
      std::vector<Player>       players;
      int                       nplayers;
    } Settings;
}

#endif // SETTINGS_HPP
