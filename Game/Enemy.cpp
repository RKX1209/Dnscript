#include <string>
#include <SDL.h>
#include <cstdio>
#include "Api.hpp"
#include "Keyboard.hpp"
#include "Enemy.hpp"
#include "Bullet.hpp"
#include "Window.hpp"
#include "Play.hpp"
#include "Frame.hpp"

Enemy::Enemy() : speed(0),life(0),bomb_num(0),graze(0),
                  move_frame(0), state(0){
  api = Api::instance();
  keyboard = Keyboard::instance();
  frame = Frame::instance();
  bullets.resize(bullet_num);
  for(int i = 0; i < bullet_num; i++){
    bullets[i] = new Bullet();
  }
  obj_pos->x = Play::win_rect.w / 2;
  obj_pos->y = 10;
  clear_state();
}

Enemy::~Enemy(){
  for(int i = 0; i < bullet_num; i++){
    delete bullets[i];
  }
}
void Enemy::shoot(int x,int y,
                  double speed,double angle,double damage,
                  int pene,int id){
}
void Enemy::shoot(int x,int y,double speed,
                  double angle,double damage,int pene,Bullet::Color color,int delay){
  for(int i = 0; i < bullet_num; i++){
      if(bullets[i]->available()){
        bullets[i]->set_type(Bullet::TYPE_NORMAL,color);
        bullets[i]->set_state(x,y,speed,angle,damage,pene);
        bullets[i]->reserve();
        Action sh_act(Action::TYPE_SHOOT);
        sh_act.set_bullet(bullets[i]);
        action_list->add_action(frame->get_next_frame(delay),sh_act);//lazy shoot
        break;
      }
  }
}
void Enemy::update(){
  int now_frame = frame->get_frame();
  //printf("%d\n",now_frame);
  while(true){
    Action action = action_list->get_action(now_frame);
    if(action.get_type() == Action::TYPE_MOVE){
      set_state(STATE_MOVE);
      move_frame = action.get_move_frame();
    }
    else if(action.get_type() == Action::TYPE_SHOOT){
      set_state(STATE_SHOOT);
    }
    else{
      break;
    }

    if(is_state(STATE_SHOOT)){
      action.get_bullet()->shoot();
      remove_state(STATE_SHOOT);
    }
  }
  if(is_state(STATE_MOVE)){
    if(move_frame > 0){
      obj_pos->x += dx;
      obj_pos->y += dy;
      move_frame--;
    }else{
      remove_state(STATE_MOVE);
    }
  }

  for(int i = 0; i < bullet_num; i++){
    if(bullets[i]->is_shoot()){
      bullets[i]->update();
    }
  }

}

void Enemy::start_move(int x,int y,int fr){
  mx = x;
  my = y;
  dx = (mx - obj_pos->x) / fr;
  dy = (my - obj_pos->y) / fr;
//printf("%d,%d\n",dx,dy);
  Action move_act(Action::TYPE_MOVE);
  move_act.set_move(x,y,dx,dy,fr);
  action_list->add_action(frame->get_frame() + 2,move_act); //move immediately
  //printf("move_y:%d,%d\n",obj_pos->y,move_y);
}

void Enemy::draw(){
  for(int i = 0; i < bullet_num; i++){
    if(bullets[i]->is_shoot()){
      bullets[i]->draw();
    }
  }
}
void Enemy::set_state(State _s){
  state |= (unsigned int)_s;
}
void Enemy::remove_state(State _s){
  state &= ~((unsigned int)_s);
}
bool Enemy::is_state(State _s){
  return (state & (unsigned int)_s);
}
