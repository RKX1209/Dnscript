#ifndef __PLAYER_HPP__
#define __PLAYER_HPP__

#include <vector>

class Object;
class Api;
class Keyboard;
class Bullet;
class Player{
private:
  Api* api;
  Keyboard* keyboard;
  static const int bullet_num = 20;
  std::vector<Bullet*>bullets;
  int x;
  int y;
public:
  Object* obj_back;
  Player();
  ~Player();
  void update();
  void draw();
  void shoot(int,int,double,double,double,int,int);

};

#endif
