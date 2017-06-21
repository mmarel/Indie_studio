#include "Game/AAI.hpp"

indie::AAI::AAI(const int &new_id)
: id(new_id),
  pos(),
  shift_ok(true),
  wait(false),
  action(indie::e_AiAction::UNKNOWN),
  direction(),
  empty_case(),
  bomb_case(),
  pos_enemy()
{
}

indie::AAI::~AAI()
{

}

const int &indie::AAI::getId()
{
  return(this->id);
}

const indie::ELookAt &indie::AAI::getDirection()
{
  return(this->direction);
}

void indie::AAI::goUp(const Map &map)
{
  shift_ok = false;
  if (map.at(0, pos.first, pos.second).getShiftX(0) < 0.1)
    shift_ok = true;
  this->action = indie::AiAction::AI_UP;
  this->direction = indie::ELookAt::NORTH;
}

void indie::AAI::goDown(const Map &map)
{
  shift_ok = false;
  if (map.at(0, pos.first, pos.second).getShiftX(0) < 0.1)
    shift_ok = true;
  this->action = indie::AiAction::AI_DOWN;
  this->direction = indie::ELookAt::SOUTH;
}

void indie::AAI::goLeft(const Map &map)
{
  shift_ok = false;
  if (map.at(0, pos.first, pos.second).getShiftY(0) < 0.1)
    shift_ok = true;
  this->action = indie::AiAction::AI_LEFT;
  this->direction = indie::ELookAt::WEST;
}

void indie::AAI::goRight(const Map &map)
{
  shift_ok = false;
  if (map.at(0, pos.first, pos.second).getShiftY(0) < 0.1)
    shift_ok = true;
  this->action = indie::AiAction::AI_RIGHT;
  this->direction = indie::ELookAt::EAST;
}

void indie::AAI::dropPikesBomb()
{
  this->action = indie::AiAction::AI_PIKESBOMB;
}

void indie::AAI::dropSquareBomb()
{
  this->action = indie::AiAction::AI_SQUAREBOMB;
}

void indie::AAI::dropTentacleBomb()
{
  this->action = indie::AiAction::AI_TENTACLEBOMB;
}

const std::pair<int, int> &indie::AAI::getPosition(const Map &map)
{
  for (int y = 0; y < static_cast<int>(map.getHeight()); y++) {
    for (int x = 0; x < static_cast<int>(map.getWidth()); x++) {
      if (map.at(0, x, y).getType(0) == static_cast<indie::OBJECTS_ID>(this->id))
        pos = {x, y};
    }
  }
  return (pos);
}

void indie::AAI::getClosestEnemy(const int &nb_players, const Map &map)
{
  pos_enemy.first = 50;
  pos_enemy.second = 50;
  for (int y = 0; y < static_cast<int>(map.getHeight()); y++) {
    for (int x = 0; x < static_cast<int>(map.getWidth()); x++) {
      for (int player_id = 1; player_id < nb_players; player_id++)
        {
          if (this->id != player_id &&
              map.at(0, x, y).getType(0) == static_cast<indie::OBJECTS_ID>(player_id)
              && (x + y) < (pos_enemy.first + pos_enemy.second)) {
                pos_enemy = {x, y};
        }
      }
    }
  }
}

const indie::e_AiAction &indie::AAI::getAction()
{
  return (this->action);
}

void indie::AAI::getEmptyCase(const Map &map)
{
  this->empty_case.clear();
  if (pos.first + 1 < static_cast<int>(map.getWidth()) && map.at(0, pos.first + 1, pos.second).getType(0) == indie::OBJECTS_ID::EMPTY)
    this->empty_case.push_back({pos.first + 1, pos.second});
  if (pos.first - 1 >= 0 && map.at(0, pos.first - 1, pos.second).getType(0)  == indie::OBJECTS_ID::EMPTY)
    this->empty_case.push_back({pos.first - 1, pos.second});
  if (pos.second + 1 < static_cast<int>(map.getHeight()) && map.at(0, pos.first, pos.second + 1).getType(0)  == indie::OBJECTS_ID::EMPTY)
    this->empty_case.push_back({pos.first, pos.second + 1});
  if (pos.second - 1 >= 0 && map.at(0, pos.first, pos.second - 1).getType(0)  == indie::OBJECTS_ID::EMPTY)
    this->empty_case.push_back({pos.first, pos.second -1});
}

void indie::AAI::getBombCase(const Map &map)
{
  this->bomb_case.clear();
  if (pos.first + 1 < static_cast<int>(map.getWidth()) && map.at(1, pos.first + 1, pos.second).getType(0) > static_cast<indie::OBJECTS_ID>(6))
    this->bomb_case.push_back({pos.first + 1, pos.second});
  if (pos.first - 1 >= 0 && map.at(1, pos.first - 1, pos.second).getType(0) > static_cast<indie::OBJECTS_ID>(6))
    this->bomb_case.push_back({pos.first - 1, pos.second});
  if (pos.second + 1 < static_cast<int>(map.getHeight()) && map.at(1, pos.first, pos.second + 1).getType(0) > static_cast<indie::OBJECTS_ID>(6))
    this->bomb_case.push_back({pos.first, pos.second + 1});
  if (pos.second - 1 >= 0 && map.at(1, pos.first, pos.second - 1).getType(0) > static_cast<indie::OBJECTS_ID>(6))
    this->bomb_case.push_back({pos.first, pos.second -1});
  if (map.at(1, pos.first, pos.second).getType(0) > static_cast<indie::OBJECTS_ID>(6))
    this->bomb_case.push_back({pos.first, pos.second});
}

void indie::AAI::run(const Map &map)
{
  bool OnBomb = true;

  wait = true;
  for (long unsigned int i = 0; i < this->empty_case.size(); i++) {
    if (this->bomb_case[0].first == this->pos.first && empty_case[i].first < this->pos.first)
      {
        OnBomb = false;
        goLeft(map);
        i = this->empty_case.size();
      }
    else if (this->bomb_case[0].first == this->pos.first && empty_case[i].first > this->pos.first)
      {
        OnBomb = false;
        goRight(map);
        i = this->empty_case.size();
      }
    else if (this->bomb_case[0].second == this->pos.second && empty_case[i].second < this->pos.second)
      {
        OnBomb = false;
        goUp(map);
        i = this->empty_case.size();
      }
    else if (this->bomb_case[0].second == this->pos.second && empty_case[i].second > this->pos.second)
      {
        OnBomb = false;
        goDown(map);
        i = this->empty_case.size();
      }
  }
  if (OnBomb == true)
    {
      for (long unsigned int i = 0; i < this->empty_case.size(); i++) {
        if (empty_case[i].second > this->pos.second)
          {
            OnBomb = true;
            goDown(map);
            i = this->empty_case.size();
          }
        else if (empty_case[i].first < this->pos.first)
          {
            OnBomb = true;
            goLeft(map);
            i = this->empty_case.size();
          }
        else if (empty_case[i].first > this->pos.first)
          {
            OnBomb = true;
            goRight(map);
            i = this->empty_case.size();
          }
        else if (empty_case[i].second < this->pos.second)
          {
            OnBomb = true;
            goUp(map);
            i = this->empty_case.size();
          }
      }
    }
}

void indie::AAI::goOnEnemy(const Map &map)
{
  for (long unsigned int i = 0; i < this->empty_case.size(); i++) {
    if (((pos_enemy.second - this->pos.second) == 1 && (pos_enemy.first- this->pos.first) == 0)
              || ((pos_enemy.second - this->pos.second) == 0 && (pos_enemy.first- this->pos.first) == 1)
              || ((pos_enemy.second - this->pos.second) == 0 && (pos_enemy.first- this->pos.first) == -1)
              || ((pos_enemy.second - this->pos.second) == -1 && (pos_enemy.first- this->pos.first) == 0))
      {
        i = this->empty_case.size();
        dropPikesBomb();
      }
    else if (pos_enemy.first < this->pos.first && empty_case[i].first < this->pos.first)
      {
        goLeft(map);
        i = this->empty_case.size();
      }
    else if (pos_enemy.first > this->pos.first && empty_case[i].first > this->pos.first)
      {
        goRight(map);
        i = this->empty_case.size();
      }
    else if (pos_enemy.second < this->pos.second && empty_case[i].second < this->pos.second)
      {
        goUp(map);
        i = this->empty_case.size();
      }
    else if (pos_enemy.second > this->pos.second && empty_case[i].second > this->pos.second)
      {
        goDown(map);
        i = this->empty_case.size();
      }
    else
      {
        this->action = indie::AiAction::UNKNOWN;
        this->direction = indie::ELookAt::SOUTH;
      }
  }
}
