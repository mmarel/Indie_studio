//
// Author: Maud Marel 
// Date: 2017-06-12 19:15:39 
//

#include <iostream>
#include "Game/keyMap.hpp"

indie::keyMap::keyMap() : act()
{
    act[indie::GameState::MENU] = std::bind(&indie::keyMap::act_menu, this);
    act[indie::GameState::SETTINGS] = std::bind(&indie::keyMap::act_settings, this);
    act[indie::GameState::SCORE] = std::bind(&indie::keyMap::act_score, this);
    act[indie::GameState::ROOM] = std::bind(&indie::keyMap::act_room, this);
}

indie::keyMap::~keyMap()
{
}

void    indie::keyMap::act_menu(indie::Event event)
{
    std::cout << "MENU" << std::endl;
}

void    indie::keyMap::act_settings(indie::Event event)
{
    std::cout << "SETTINGS" << std::endl;
}

void    indie::keyMap::act_score(indie::Event event)
{
    std::cout << "SCORE" << std::endl;
}

void    indie::keyMap::act_room(indie::Event event)
{
    std::cout << "ROOM" << std::endl;
}

void    indie::keyMap::manage_keyMap(indie::GameState &gameState, indie::Event event)
{
    std::cout << "I'm here!" << std::endl;
    act[gameState](event);
}