#ifndef __BULLET_HPP__
#define __BULLET_HPP__

#include <SDL.h>

class Api;

class Bullet{
public:
  enum State{
    STATE_SHOT,
    STATE_NONE,
  };
private:
  Api* api;
  int id;
  SDL_Rect draw_rect;
  int x;
  int y;
  double speed;
  double angle;
  double damage;
  int pene;
  State state;
public:
  Object* obj_back;
  Bullet();
  ~Bullet();
  void update();
  void draw();
  bool available();
  int get_id();
  void shoot(int,int,double,double,double,int);
};

#endif
