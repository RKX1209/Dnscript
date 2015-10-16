#ifndef __CLEAR_HPP__
#define __CLEAR_HPP__
class Object;
class Game;
class Api;
class Keyboard;

class Clear{
private:
  Api* api;
  Keyboard* keyboard;
public:
  Object* obj_back;
  Clear();
  ~Clear();
  void update(Game*);
  void draw();
};

#endif
