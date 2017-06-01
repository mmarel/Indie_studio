//
// Author: Maud Marel
// Date: 2017-05-23 14:09:04
//

#include <iostream>
#include <chrono>
#include <thread>
#include <memory>
#include "Common/Core.hh"

indie::Core::Core() : _gameState(indie::GameState::MENU)
{
}

indie::Core::~Core()
{
}

indie::Core::Core(Core const &copy) : _gameState(copy._gameState)
{
  (void)copy;
}

indie::Core &indie::Core::operator=(Core const &copy)
{
  (void)copy;
    return (*this);
}

indie::GameState    indie::Core::getGameState() const
{
    return (_gameState);
}

void    indie::Core::setGameState(const indie::GameState state)
{
    _gameState = state;
}

void    indie::Core::load_sound_lib()
{
}

void    indie::Core::display_game(indie::Gfx &_gfx)
{
    _gfx.display();
    _gfx.clear();
}

void    indie::Core::display_menu(indie::Gfx &_gfx)
{
    _gfx.display();
    _gfx.clear();
}

void    indie::Core::display_loop()
{
    int state;
    //std::unique_ptr<indie::Gfx> _gfx = std::make_unique<indie::Gfx>();
    indie::Gfx _gfx;

    /*
    ** Loop en fonction des GameState
    */
    while ((state = getGameState()) != indie::GameState::QUIT)
    {
        switch(state)
        {
            case indie::GameState::LOADING :
            {
                std::cout << "LOADING" << std::endl;
                load_sound_lib();
            }
            case indie::GameState::INGAME :
            {
                std::cout << "INGAME" << std::endl;
                display_game(_gfx);
            }
            case indie::GameState::MENU :
            {
                std::cout << "MENU" << std::endl;
                display_menu(_gfx);
            }
            default:
                break;
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    }
}

void    indie::Core::display()
{

    std::cout << "display Core" << std::endl;

    //display_loop(_gfx);
}