#ifndef __LOAD_HPP__
#define __LOAD_HPP__
class Object;
class Game;
class Api;
class Keyboard;

class Load{
private:
  Api* api;
  Keyboard* keyboard;
  bool loading;
public:
  Object* obj_back;
  Load();
  ~Load();
  void update(Game*);
  void draw();
};

#endif
