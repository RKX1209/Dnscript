#ifndef __PLAY_HPP__
#define __PLAY_HPP__
#include <SDL.h>
#include <deque>
#include <string>
#include <fstream>
#include <iostream>
#include <map>
#include <vector>
#include <list>

#include "Interprter.hpp"

class Object;
class Game;
class Api;
class Keyboard;
class Player;
class Enemy;
class player_test;
class enemy_test;
class Window;

class Play{
private:
  Api* api;
  Keyboard* keyboard;
  Player* player;
  std::deque<Enemy*> enemies;
  player_test* p_test;
  enemy_test* e_test;
  Dnlang::Interprter *interp;
public:
  static SDL_Rect win_rect;
  Object* obj_back;
  Play();
  ~Play();
  void update(Game*);
  void draw();
  static bool in_monitor(int,int);
};

#endif
