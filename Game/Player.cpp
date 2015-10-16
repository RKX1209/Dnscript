#include <string>
#include "Api.hpp"
#include "Object.hpp"
#include "Keyboard.hpp"
#include "Player.hpp"
#include "Bullet.hpp"

Player::Player(){
  api = Api::instance();
  keyboard = Keyboard::instance();
  obj_back = new Object();
  bullets.resize(bullet_num);
  for(int i = 0; i < bullet_num; i++){
    bullets[i] = new Bullet();
  }
  x = 0;
  y = 0;
}

Player::~Player(){
  delete obj_back;
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
}
void Player::draw(){
  for(int i = 0; i < bullet_num; i++){
    if(!bullets[i]->available()){
      bullets[i]->draw();
    }
  }
}
