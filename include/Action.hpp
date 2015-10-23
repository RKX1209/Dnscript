#ifndef __ACTION_HPP__
#define __ACTION_HPP__

#include <map>
#include <deque>

class Bullet;
class Action{
public:
  enum Type{
    TYPE_MOVE,
    TYPE_SHOOT,
    TYPE_NONE,
  };
private:
  Type type;
  /* Move Action */
  int mx;
  int my;
  int dx;
  int dy;
  int move_frame;
  /* Shoot Action */
  Bullet* bullet;
public:
  Action(Type _type){ type = _type; }
  ~Action(){}
  Type get_type(){ return type; }
  void set_move(int _x,int _y,int _dx,int _dy,int _mframe){ mx = _x; my = _y; dx = _dx; dy = _dy; move_frame = _mframe; }
  void set_bullet(Bullet* _bullet){ bullet = _bullet; }
  int get_move_frame(){ return move_frame; }
  int get_dx(){ return dx; }
  int get_dy(){ return dy; }
  Bullet* get_bullet(){ return bullet; }
};

class ActionList{
private:
  std::map<int, std::deque<Action> > actions;
public:
  void add_action(int _f,Action act){
    if(actions.find(_f) == actions.end()){
      actions[_f] = std::deque<Action>();
    }
    actions[_f].push_back(act);
  }
  Action get_action(int _f){
    if(actions.find(_f) == actions.end()){
      return Action(Action::TYPE_NONE);
    }
    Action res = actions[_f].front();
    actions[_f].pop_front();
    return res;
  }
};

#endif
