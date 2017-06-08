//
// Core.hh for coore in /home/marelm/EPITECH/Projects_tek2/C++_II/cpp_indie_studio
//
// Made by maud.marel@epitech.eu
// Login   <maud.marel@epitech.eu>
//
// Started on  Thu May  4 16:03:42 2017 maud.marel@epitech.eu
// Last update Tue Jun  6 15:53:13 2017 maud.marel@epitech.eu
//

#ifndef CORE_HPP_
# define CORE_HPP_

#include "Interfaces/GameState.hpp"
#include "Graphical/Gfx.hpp"
#include "Interfaces/IGame.hpp"
#include "Interfaces/Sound.hpp"

namespace indie
{

  class	Core
  {
    private:

      indie::GameState          _gameState;
      //indie::Gfx              _gfx;
      indie::IGame              *_gameLoad;
      std::vector<indie::Sound> _sounds;

    public:
      Core();
      ~Core();

      Core(Core const &);
      Core  &operator=(Core const &);

      indie::GameState  getGameState() const;
      void              setGameState(const indie::GameState);
      void              load_sound_lib();
      void              display_game(indie::Gfx &);
      void              display_menu(indie::Gfx &);
      void              display_loop();
      void              getEventGame(indie::Gfx &);
  };
}

#endif /* !CORE_HPP_ */
