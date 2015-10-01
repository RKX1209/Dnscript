#ifndef __SELECT_HPP__
#define __SELECT_HPP__
class Object;
class Dnscript;
class Api;
class Select{
private:
  Api* api;
public:
  Object* obj_back;
  Select();
  ~Select();
  void update(Dnscript*);
  void draw();
};

#endif
