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
        getBombCase(new_map);
        getPosition(new_map);
        for (long unsigned int i = 0; i < this->empty_case.size(); i++) {
          std::cout << "x=" << empty_case[i].first << " y=" << empty_case[i].second << std::endl;
        }
        if (shift_ok == true)
          {
            std::cerr << pos.first << " " << pos.second << '\n';
            std::cerr << "------------------------------------" << '\n';
            if (bomb_case.size() != 0)
              {
                run(new_map);
              }
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
      /*}
    else
      {
        getEmptyCase(new_map);
        getPosition(new_map);
        if (new_map.at(0, bomb_case[0].first, bomb_case[0].second).getType(0) == static_cast<indie::OBJECTS_ID>(0))
          {
            std::cerr << "wait terminé" << '\n';
            wait = false;
          }
        else
          {
            std::cerr << " wait " << '\n';
            for (long unsigned int i = 0; i < this->empty_case.size(); i++)
              {
                if (this->bomb_case[0].first == this->pos.first && empty_case[i].first < this->pos.first)
                  {
                    goLeft(new_map);
                    i = this->empty_case.size();
                  }
                else if (this->bomb_case[0].first == this->pos.first && empty_case[i].first > this->pos.first)
                  {
                    goRight(new_map);
                    i = this->empty_case.size();
                  }
                else if (this->bomb_case[0].second == this->pos.second && empty_case[i].second < this->pos.second)
                  {
                    goUp(new_map);
                    i = this->empty_case.size();
                  }
                else if (this->bomb_case[0].second == this->pos.second && empty_case[i].second > this->pos.second)
                  {
                    goDown(new_map);
                    i = this->empty_case.size();
                  }
            }
          }
      }*/
}
