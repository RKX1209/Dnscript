#ifndef __ENEMY_HPP__
#define __ENEMY_HPP__

#include <vector>
#include "Object.hpp"

class Object;
class Api;
class Keyboard;
class Bullet;
class Frame;
class Enemy : public Object{
public:
  enum State{
    STATE_MOVE = 1,
    STATE_SHOOT = 2,
  };
private:
  Api* api;
  Keyboard* keyboard;
  static const int bullet_num = 500;
  std::vector<Bullet*>bullets;
  unsigned int state;
  Frame* frame;
  int speed;
  int life;
  int bomb_num;
  int graze;
  int move_frame;
public:
  Enemy();
  ~Enemy();
  void update();
  void draw();
  virtual void shoot(int,int,double,double,double,int,int);
  virtual void shoot(int,int,double,double,double,int,Bullet::Color,int);
  void start_move(int,int,int);
  virtual void set_x(int _x){ obj_pos->x = _x; }
  virtual void set_y(int _y){ obj_pos->y = _y; }
  virtual int get_x(){ return obj_pos->x; }
  virtual int get_y(){ return obj_pos->y; }
  virtual int get_mx(){ return mx; }
  virtual int get_my(){ return my; }
  virtual int get_width(){ return obj_rect->w; }
  virtual int get_height(){ return obj_rect->h; }
  virtual void set_speed(int _speed){ speed = _speed; }
  virtual void set_life(int _life){ life = _life; }
  virtual void set_bomb_num(int _bnum){ bomb_num = _bnum; }
  virtual void set_graze(int _graze){ graze = _graze; }
  void set_state(State);
  void remove_state(State);
  bool is_state(State);
  void clear_state(){ state = 0; }
};

#endif
