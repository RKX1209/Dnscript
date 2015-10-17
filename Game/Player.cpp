#include <string>
#include <SDL.h>
#include <cstdio>
#include "Api.hpp"
#include "Keyboard.hpp"
#include "Player.hpp"
#include "Bullet.hpp"
#include "Window.hpp"

Player::Player() : speed(0),life(0),bomb_num(0),graze(0){
  api = Api::instance();
  keyboard = Keyboard::instance();
  bullets.resize(bullet_num);
  for(int i = 0; i < bullet_num; i++){
    bullets[i] = new Bullet();
  }
  x = Window::win_rect.w / 2;
  y = 10;
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
      bullets[i]->shoot(x,y,speed,angle,damage,pene);
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
  int dx = 0; int dy = 0;
  if(keyboard->is_keyon(SDLK_LEFT)){
    dx = -speed;
  }else if(keyboard->is_keyon(SDLK_RIGHT)){
    dx = speed;
  }else if(keyboard->is_keyon(SDLK_UP)){
    dy = -speed;
  }else if(keyboard->is_keyon(SDLK_DOWN)){
    dy = speed;
  }
  x += dx;
  y += dy;
}

void Player::draw(){
  for(int i = 0; i < bullet_num; i++){
    if(!bullets[i]->available()){
      bullets[i]->draw();
    }
  }
}
