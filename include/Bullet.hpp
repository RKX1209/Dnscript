#ifndef __BULLET_HPP__
#define __BULLET_HPP__

#include <SDL.h>

class Api;
class Object;
class Bullet{
public:
  enum Type{
    TYPE_NORMAL,
    TYPE_BOMB,
  };
  enum State{
    STATE_SHOT,
    STATE_RESERVE,
    STATE_NONE,
  };
  enum Color{
    RED,
    GREEN,
    BLUE,
    YELLOW,
    PURPLE,
    LIGHT_BLUE,
    GRAY,
    ORANGE,
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
  Type type;
  Color color;
public:
  Object* obj_back;
  Bullet();
  ~Bullet();
  void update();
  void draw();
  bool available();
  bool is_shoot();
  int get_id();
  void shoot();
  void reserve();
  void set_state(int,int,double,double,double,int);
  void set_type(Type,Color);
  void load_data(Type,Color);
};

#endif
