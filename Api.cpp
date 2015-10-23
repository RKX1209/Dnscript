#include <iostream>
#include <string>
#include <cstdio>
#include <unistd.h>
#include <SDL2_rotozoom.h>
#include "Object.hpp"
#include "Api.hpp"
#include "Dnscript.hpp"
#include "Window.hpp"
#include "Play.hpp"


Api* Api::mInstance = 0;

Api* Api::instance(){
    return mInstance;
}

void Api::create(){
  try{
    if(mInstance) throw "[*ERROR*] Api::create() cannnot create instance twice";
    mInstance = new Api();
  }catch(const char *error){
    fprintf(stderr,"%s\n",error);
    abort();
  }
}

void Api::destroy(){
  delete mInstance;
  mInstance = 0;
}

Api::Api(){
  keyboard = Keyboard::instance();
}
/* ### API list ### */
/* Graphics */
void Api::LoadGraphic(Object* target,std::string filename){
  target->set_image(IMG_Load(filename.c_str()));
}

void Api::SetTexture(Object* target,std::string filename){
  SDL_Renderer* renderer = Window::renderer;
  SDL_Texture* tex = SDL_CreateTextureFromSurface(renderer,target->get_image());
  target->set_texture(tex);
}

void Api::SetGraphicRect(Object* target,Uint32 sx,Uint32 sy,Uint32 dx,Uint32 dy){
  Uint32 width = dx - sx;
  Uint32 height = dy - sy;
  target->set_obj_rect(sx,sy,width,height);
}

void Api::SetGraphicAngle(Object* target,Uint32 angle){
  rotozoomSurface(target->get_image(),angle,1,1);
  SetTexture(target,"dummy"); //rebind
}

void Api::DrawGraphic(Object* target,Uint32 x,Uint32 y){
  target->set_obj_pos(x,y);
  SDL_Renderer* renderer = Window::renderer;
  SDL_Rect *src = target->get_obj_rect();
  SDL_Rect * dest = target->get_obj_pos();
  SDL_RenderCopy(renderer, target->get_texture(),src,dest);
}

/* Status*/
void Api::SetSpeed(Object* target,int speed){
  target->set_speed(speed);
}
void Api::SetLife(Object* target,int life){
  target->set_life(life);
}
void Api::SetX(Object* target,int x){
  target->set_x(x);
}
void Api::SetY(Object* target,int y){
  target->set_y(y);
}
int Api::GetPlayerX(Object* target){
  return target->get_x();
}
int Api::GetPlayerY(Object* target){
  return target->get_y();
}
int Api::GetSpeedX(Object* target){
  return target->get_dx();
}
int Api::GetSpeedY(Object* target){
  return target->get_dy();
}
int Api::GetX(Object* target){
  return target->get_x();
}
int Api::GetY(Object* target){
  return target->get_y();
}
int Api::GetCenterX(){
  return Play::win_rect.w / 2;
}
int Api::GetCenterY(){
  return Play::win_rect.h / 2;
}

/* Danmaku */
void Api::CreatePlayerShot01(Object* target,int x,int y,
                            double speed,double angle,double damage,
                            int pene,int id){
  target->shoot(x,y,speed,angle,damage,pene,id);
}
void Api::CreateShot01(Object* target,int x,int y,
                      double speed,double angle,Bullet::Color color,int delay){
  target->shoot(x,y,speed,angle,999999,10000,color,delay);
}

/* Action */
void Api::SetMovePosition02(Object* target,int x,int y,int frame){
  target->start_move(x,y,frame);
}

/* Keyboard */
Api::KeyState Api::GetKeyState(SDL_Keycode key){
  if(keyboard->is_keyon(key)) return KEY_PUSH;
  if(keyboard->is_keytoggle(key)) return KEY_HOLD;
  if(keyboard->is_keyoff(key)) return KEY_RELEASE;
}

/* Other */
std::string Api::GetCurrentScriptDirectory(){
  char buf[256];
  getcwd(buf,256);
  std::string path = buf;
  return path;
}

/* Unofficial API (hidden) */
void Api::RenderClear(){
  SDL_RenderClear(Window::renderer);
}
void Api::RenderPresent(){
  SDL_RenderPresent(Window::renderer);
}
