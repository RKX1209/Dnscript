#ifndef __GAME_HPP__
#define __GAME_HPP__

#include "Dnscript.hpp"

class Load;
class Clear;
class Play;
class Menu;


class Game{
public:
  enum SeqID{
    SEQ_LOAD,
    SEQ_CLEAR,
    SEQ_PLAY,
    SEQ_MENU,
    SEQ_NONE,
  };
private:
  Load* load;
  Clear* clear;
  Play* play;
  Menu* menu;
  SeqID next;
public:
  Game();
  ~Game();
  void update(Dnscript*);
  void draw();
  void moveTo(SeqID);
  void load_data();
};

#endif
