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
  bullets.resize(bullet_num);
  for(int i = 0; i < bullet_num; i++){
    bullets[i] = new Bullet();
  }
  obj_pos->x = Play::win_rect.w / 2;
  obj_pos->y = Play::win_rect.h - obj_rect->h - 10;
}

Player::~Player(){
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

void Player::draw(){
  for(int i = 0; i < bullet_num; i++){
    if(!bullets[i]->available()){
      bullets[i]->draw();
    }
  }
}
