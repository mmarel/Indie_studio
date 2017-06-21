#ifndef PLAYER_HPP
# define PLAYER_HPP

# include <string>
# include <map>
# include <vector>
# include <algorithm>
# include "Interfaces/Event.hpp"
# include "Interfaces/ITile.hpp"
# include "Interfaces/IAI.hpp"
# include "Game/Settings.hpp"
# include "Game/ModelsId.hpp"

namespace indie {
  class Player {
    public:
      Player(size_t,
              ELookAt dir = ELookAt::SOUTH,
              PlayerType = PlayerType::PLAYER_HUMAN,
              IA_LEVEL = IA_UNKNOWN);
      ~Player() {};

    public:
      size_t getId() const { return _id; }
      indie::OBJECTS_ID getBombType() const { return _bombType; };
      const std::map<std::string, KeyboardKey> &getBindings() const { return _bindings; };
      int getScore() const { return _score; }
      bool hasBomb(size_t) const;
      bool isAlive() const { return _alive; }

    public:
      void setBombType(indie::OBJECTS_ID bombType) { _bombType = bombType; }
      void bomb(size_t id) { _bombs.push_back(id); }
      void removeBomb(size_t);
      void updateScore(int points) { _score += points; }
      void die() { _score -= 200; _alive = false; }

    private:
      size_t                             _id;
      std::map<std::string, KeyboardKey> _bindings;
      OBJECTS_ID                         _bombType;
      std::vector<size_t>                _bombs;
      int                                _score;
      bool                               _alive;
      PlayerType                         _type;
      IA_LEVEL                           _level;
      std::unique_ptr<IAI>               _ai;
    };
};

#endif // PLAYER_HPP
