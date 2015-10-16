#ifndef __PLAY_HPP__
#define __PLAY_HPP__
class Object;
class Game;
class Api;
class Keyboard;
class Player;

class Play{
private:
  Api* api;
  Keyboard* keyboard;
  Player* player;
public:
  Object* obj_back;
  Play();
  ~Play();
  void update(Game*);
  void draw();
  static bool in_monitor(int,int);
};

#endif
