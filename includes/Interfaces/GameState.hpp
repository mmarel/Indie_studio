//
// Author: Marwane Khsime 
// Date: 2017-05-22 17:49:33 
//
// Last Modified by:   Marwane Khsime 
// Last Modified time: 2017-05-22 17:49:33
//
#ifndef GAMESTATE_HPP_
#define GAMESTATE_HPP_

#include <vector>
#include <map>
#include "irr/irrlicht.h"

namespace indie
{

    ///
    /// \enum TileTypeEvolution
    /// \brief Type of map tile
    ///
    enum TileTypeEvolution
    {
        //! Empty tile
        EMPTY = 0,
        
        //! Block tile
        BLOCK,
        
        //! Obstacle tile
        OBSTACLE,
        
        //! Enemy tile
        ENEMY,
        
        //! Enemy shot tile
        SHOT_ENEMY,
        
        //! Player shot tile
        SHOT_PLAYER,
        
        //! Powerup tile
        POWERUP,
        
        //! Player tile
        PLAYER,
        
        //! Food tile
        FOOD,
    };


    ///
    /// \enum GameState
    /// \brief Describes current game state
    ///
    enum GameState
    {
        //! Unknown game state
        NONE = -1,

        //! Loading (need to load sounds / sprites)
	    LOADING,

        //! Splash screen
        SPLASH_SCREEN,

        //! In game
        INGAME,

        //! In menu
        MENU,

        //! Quitting
        QUIT,

        //! Number of game states
        NB_GAME_STATE
    };

    class EventKey : public irr::IEventReceiver
    {
        public:
            EventKey();
            virtual ~EventKey() {};

            virtual bool    OnEvent(const irr::SEvent& event);
            int             getKeyPressed() const;
            bool            IsKeyDown(irr::EKEY_CODE keyCode) const;

        private:
            bool            keyMap[irr::KEY_KEY_CODES_COUNT];
    };
}
#endif // !GAMESTATE_HPP_
