#ifndef __TITLE_HPP__
#define __TITLE_HPP__
class Object;
class Dnscript;
class Api;
class Title{
private:
  Api* api;
public:
  Object* obj_back;
  Title();
  ~Title();
  void update(Dnscript*);
  void draw();
};

#endif
