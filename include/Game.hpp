#ifndef __GAME_HPP__
#define __GAME_HPP__
class Object;
class Dnscript;
class Api;
class Game{
private:
  Api* api;
public:
  Game();
  ~Game();
  void update(Dnscript*);
  void draw();
};

#endif
