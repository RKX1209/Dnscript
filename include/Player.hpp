#ifndef __PLAYER_HPP__
#define __PLAYER_HPP__

#include <vector>
#include "Object.hpp"

class Object;
class Api;
class Keyboard;
class Bullet;
class Player : public Object{
private:
  Api* api;
  Keyboard* keyboard;
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
  void set_x(int _x){ x = _x; }
  void set_y(int _y){ y = _y; }
  int get_x(){ return x; }
  int get_y(){ return y; }
  void set_speed(int _speed){ speed = _speed; }
  void set_life(int _life){ life = _life; }
  void set_bomb_num(int _bnum){ bomb_num = _bnum; }
  void set_graze(int _graze){ graze = _graze; }
};

#endif
