#include <string>
#include <math.h>
#include "Api.hpp"
#include "Object.hpp"
#include "Bullet.hpp"
#include "Play.hpp"

Bullet::Bullet(){
  api = Api::instance();
  obj_back = new Object();

  state = STATE_NONE;
  id = 1;
  std::string filename("img/bullets.png");
  obj_back = new Object();
  api->LoadGraphic(obj_back,filename);
  api->SetTexture(obj_back,filename);
  set_type(TYPE_NORMAL,RED);
}

Bullet::~Bullet(){
  delete obj_back;
}

void Bullet::update(){
  if(Play::in_monitor(x,y)){
    x += speed * cos(angle * M_PI / 180.0);
    y += speed * sin(angle * M_PI / 180.0);
  }else{
    state = STATE_NONE;
  }
}
void Bullet::draw(){
  api->DrawGraphic(obj_back,x,y);
}
void Bullet::set_state(int x,int y,
                  double speed,double angle,double damage,
                  int pene){
  this->x = x;
  this->y = y;
  this->speed = speed;
  this->angle = angle;
  this->damage = damage;
  this->pene = pene;
}
void Bullet::shoot(){
  state = STATE_SHOT;
}
void Bullet::reserve(){
  state = STATE_RESERVE;
}
void Bullet::set_type(Type _type,Color _color){
  type = _type;
  color = _color;
  load_data(type,color);
}
void Bullet::load_data(Type _type,Color _color){
  /* FIXME: These datas must separeted from source code. */
  int size = 20;
  api->SetGraphicRect(obj_back,(int)color * size,0,((int)color + 1) * size,size);
}

bool Bullet::available(){
  return state == STATE_NONE;
}
int Bullet::get_id(){
  return id;
}
