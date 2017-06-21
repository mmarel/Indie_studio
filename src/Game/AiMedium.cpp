#include "Game/AiMedium.hpp"

indie::AiMedium::AiMedium(const int &new_id)
: indie::AAI(new_id)
{
}

indie::AiMedium::~AiMedium()
{

}

void indie::AiMedium::loop(const Map &new_map,
                          const int &nb_players) {
    /*if (wait == false)
      {*/
        getEmptyCase(new_map);
        //getBombCase(new_map);
        getPosition(new_map);
        for (long unsigned int i = 0; i < this->empty_case.size(); i++) {
          //std::cout << "x=" << empty_case[i].first << " y=" << empty_case[i].second << std::endl;
        bool isAlive = false;
        for (int y = 0; y < static_cast<int>(new_map.getHeight()); y++) {
          for (int x = 0; x < static_cast<int>(new_map.getWidth()); x++) {
          if (new_map.at(0, x, y).getType(0) == static_cast<indie::OBJECTS_ID>(this->id))
            {
               isAlive = true;
            }
          }
        }
        if (isAlive)
          {
            //std::cerr << pos.first << " " << pos.second << '\n';
            //std::cerr << "------------------------------------" << '\n';
            /*if (bomb_case.size() != 0)
              getPosition(new_map);*/
          //  std::cout << "x : " << pos.first << " shift :" << new_map.at(0, pos.first, pos.second).getShiftX(0)
            //          << "y : " << pos.first << " shift :" << new_map.at(0, pos.first, pos.second).getShiftY(0) << std::endl;
            getEmptyCase(new_map);
            getSafeCase(new_map);
            if (shift_ok == true)
              {
                if (safe_case[pos.second][pos.first] == false
                    || new_map.at(1, pos.first, pos.second).getType(0) > static_cast<indie::OBJECTS_ID>(6))
                  run(new_map);
                else
                  {
                    getClosestEnemy(nb_players, new_map);
                    goOnEnemy(new_map);
                  }
              }
            else
              {
                if (direction == indie::ELookAt::NORTH)
                  goUp(new_map);
                else if (direction == indie::ELookAt::SOUTH)
                  goDown(new_map);
                else if (direction == indie::ELookAt::EAST)
                  goRight(new_map);
                else if (direction == indie::ELookAt::WEST)
                  goLeft(new_map);
              }
        }
      }
}
