#ifndef __DNSCRIPT_HPP__
#define __DNSCRIPT_HPP__

class Title;
class Select;
class Game;
class Event;

class Dnscript{
public:
  enum SeqID{
    SEQ_TITLE,
    SEQ_STAGE_SELECT,
    SEQ_GAME,
    SEQ_NONE,
  };
private:
  Title* title;
  Select* select;
  Game* game;
  SeqID next;
public:
  Dnscript(void);
  ~Dnscript(void);
  void update(void);
  void draw(void);
  void moveTo(SeqID);
};

#endif
