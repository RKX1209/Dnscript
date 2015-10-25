#ifndef __PLAYER_HPP__
#define __PLAYER_HPP__

#include <vector>
#include <string>
#include "Object.hpp"

class Object;
class Api;
class Keyboard;
class Bullet;
class Player : public Object{
public:
  enum State{
    STATE_CUTIN = 1,
  };
private:
  Api* api;
  Keyboard* keyboard;
  Object* obj_cutin;
  unsigned int state;
  static const int bullet_num = 40;
  std::vector<Bullet*>bullets;
  int speed;
  int life;
  int bomb_num;
  int graze;
public:
  Player();
  ~Player();
  void update();
  void draw();
  void shoot(int,int,double,double,double,int,int);
  void move();
  void set_x(int _x){ obj_pos->x = _x; }
  void set_y(int _y){ obj_pos->y = _y; }
  int get_x(){ return obj_pos->x; }
  int get_y(){ return obj_pos->y; }
  int get_width(){ return obj_rect->w; }
  int get_height(){ return obj_rect->h; }
  void set_speed(int _speed){ speed = _speed; }
  void set_life(int _life){ life = _life; }
  void set_bomb_num(int _bnum){ bomb_num = _bnum; }
  void set_graze(int _graze){ graze = _graze; }
  void CutIn(std::string,std::string,int,int,int,int);
  void set_state(State);
  void remove_state(State);
  bool is_state(State);
  void clear_state(){ state = 0; }
};

#endif
