#include <string>
#include <SDL.h>
#include <cstdio>
#include "Api.hpp"
#include "Keyboard.hpp"
#include "Player.hpp"
#include "Bullet.hpp"
#include "Window.hpp"
#include "Play.hpp"

Player::Player() : speed(0),life(0),bomb_num(0),graze(0){
  api = Api::instance();
  keyboard = Keyboard::instance();
  obj_cutin = new Object();
  bullets.resize(bullet_num);
  for(int i = 0; i < bullet_num; i++){
    bullets[i] = new Bullet();
  }
  obj_pos->x = Play::win_rect.w / 2;
  obj_pos->y = Play::win_rect.h - obj_rect->h - 10;
}

Player::~Player(){
  delete obj_cutin;
  for(int i = 0; i < bullet_num; i++){
    delete bullets[i];
  }
}
void Player::shoot(int x,int y,
                  double speed,double angle,double damage,
                  int pene,int id){
  for(int i = 0; i < bullet_num; i++){
    if(bullets[i]->available() && bullets[i]->get_id() == id){
      bullets[i]->set_state(x,y,speed,angle,damage,pene);
      bullets[i]->shoot();
      //printf("shoot %d\n",i);
      break;
    }
  }
}

void Player::update(){
  for(int i = 0; i < bullet_num; i++){
    if(!bullets[i]->available()){
      bullets[i]->update();
    }
  }
  move();
  if(is_state(STATE_CUTIN)){
  }
}

void Player::move(){
  dx = 0; dy = 0;
  if(keyboard->is_keyon(SDLK_LEFT)){
    dx = -speed;
  }else if(keyboard->is_keyon(SDLK_RIGHT)){
    dx = speed;
  }
  if(keyboard->is_keyon(SDLK_UP)){
    dy = -speed;
  }else if(keyboard->is_keyon(SDLK_DOWN)){
    dy = speed;
  }
  if(!Play::in_monitor(obj_pos->x + dx,obj_pos->y + dy)) return;
  obj_pos->x += dx;
  obj_pos->y += dy;
}
void Player::CutIn(std::string label,std::string img,
                    int x1,int y1,int x2,int y2){
  api->LoadGraphic(obj_cutin,img);
  api->SetTexture(obj_cutin,img);
                      printf("cutin\n");
  api->SetGraphicRect(obj_cutin,x1,y1,x2,y2);
  set_state(STATE_CUTIN);
}

void Player::draw(){
  for(int i = 0; i < bullet_num; i++){
    if(!bullets[i]->available()){
      bullets[i]->draw();
    }
  }
  if(is_state(STATE_CUTIN)){
      api->DrawGraphic(obj_cutin,20,100);
  }
}

void Player::set_state(State _s){
  state |= (unsigned int)_s;
}
void Player::remove_state(State _s){
  state &= ~((unsigned int)_s);
}
bool Player::is_state(State _s){
  return (state & (unsigned int)_s);
}
