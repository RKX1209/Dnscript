#include <string>
#include <math.h>
#include "Api.hpp"
#include "Object.hpp"
#include "Bullet.hpp"
#include "Play.hpp"

Bullet::Bullet(){
  api = Api::instance();
  obj_back = new Object();
  std::string filename("img/bullet.png");
  obj_back = new Object();
  api->LoadGraphic(obj_back,filename);
  api->SetTexture(obj_back,filename);
  SDL_Surface* image = obj_back->get_image();
  api->SetGraphicRect(obj_back,1,1,31,31);
  state = STATE_NONE;
  id = 1;
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
void Bullet::shoot(int x,int y,
                  double speed,double angle,double damage,
                  int pene){
  this->x = x;
  this->y = y;
  this->speed = speed;
  this->angle = angle;
  this->damage = damage;
  this->pene = pene;
  state = STATE_SHOT;
}

bool Bullet::available(){
  return state == STATE_NONE;
}
int Bullet::get_id(){
  return id;
}
