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
    /// \enum GameState
    /// \brief Describe current game state
    ///
    enum GameState
    {
        NONE = -1, /// Unknown game state
	LOADING, /// The game was just loaded (need to load sounds and sprites)
        INGAME, /// In game
        MENU, /// In menu
        QUIT, /// Quitting
        NB_GAME_STATE /// Number of game states
    };

    ///
    /// \enum TileTypeEvolution
    /// \brief Type of map tile
    ///
    enum TileTypeEvolution
    {
        EMPTY = 0, /// Empty tile
        BLOCK, /// Block tile
        OBSTACLE, /// Obstacle tile
        ENEMY, /// Enemy tile
        SHOT_ENEMY, /// Enemy shot tile
        SHOT_PLAYER, /// Player shot tile
        POWERUP, /// Powerup tile
        PLAYER, /// Player tile
        FOOD, /// Food tile
    };

    class EventKey : public irr::IEventReceiver
    {
    public:
        EventKey()
        {
            for (int i = 0; i < irr::KEY_KEY_CODES_COUNT; ++i)
                KeyIsDown[i] = false;
        }

        virtual bool  OnEvent(const irr::SEvent& event)
        {
            if (event.EventType == irr::EET_KEY_INPUT_EVENT)
                KeyIsDown[event.KeyInput.Key] = event.KeyInput.PressedDown;
            return (false);
        }

        virtual bool IsKeyDown(irr::EKEY_CODE keyCode) const
        {
            return KeyIsDown[keyCode];
        }

    private:
        bool    KeyIsDown[irr::KEY_KEY_CODES_COUNT];
    };
}
#endif // !GAMESTATE_HPP_
