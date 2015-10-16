#ifndef __MENU_HPP__
#define __MENU_HPP__
class Object;
class Game;
class Api;
class Keyboard;

class Menu{
private:
  Api* api;
  Keyboard* keyboard;
public:
  Object* obj_back;
  Menu();
  ~Menu();
  void update(Game*);
  void draw();
};

#endif
