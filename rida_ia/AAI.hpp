#ifndef AAI_HPP
# define AAI_HPP

#include "Interfaces/IAI.hpp"

namespace indie {

  class AAI : public IAI
  {
    protected:
      int                 id;
      bool  shift_ok;
      bool  wait;
      indie::AiAction     action;
      indie::ELookAt      direction;
      std::pair<int, int> pos;
      std::vector<std::pair<int, int>> empty_case;
      std::vector<std::pair<int, int>> bomb_case;
      std::pair<int, int> pos_enemy;
    public:
      AAI(const int &new_id, const std::pair<int, int> &new_pos, const indie::ELookAt &new_direction);
      virtual ~AAI();
      virtual const int &getId();
      virtual const ELookAt &getDirection();
      virtual void goUp(const Map &);
      virtual void goDown(const Map &);
      virtual void goLeft(const Map &);
      virtual void goRight(const Map &);
      virtual void dropPikesBomb();
      virtual void dropSquareBomb();
      virtual void dropTentacleBomb();
      virtual const std::pair<int, int> &getPosition(const Map &);
      virtual void getClosestEnemy(const int &, const Map &);
      virtual const indie::e_AiAction &getAction();
      virtual void getEmptyCase(const Map &);
      virtual void getBombCase(const Map &);
      virtual void run(const Map &map);
      virtual void goOnEnemy(const Map &map);
      virtual void loop(const Map &, const int &) = 0;
  };

};

#endif /* AAI_HPP */