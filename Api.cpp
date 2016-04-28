#include <iostream>
#include <string>
#include <cstdio>
#include <unistd.h>
#include <fstream>
#include <map>
#include <vector>
#include <list>
#include <SDL2_rotozoom.h>
#include "Object.hpp"
#include "Api.hpp"
#include "Dnscript.hpp"
#include "Window.hpp"
#include "Interprter.hpp"
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
int Api::GetMX(Object* target){
  return target->get_mx();
}
int Api::GetMY(Object* target){
  return target->get_my();
}
int Api::GetW(Object* target){
  return target->get_width();
}
int Api::GetH(Object* target){
  return target->get_height();
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

/* SpellCard */
void Api::CutIn(Object* target,std::string label,std::string img,int x1,int y1,int x2,int y2){
  target->CutIn(label,img,x1,y1,x2,y2);
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


/* ### ABI list ### */
/* Graphics */
void Api::_LoadGraphic(Object* target,double filename){
  std::string *filename_s = reinterpret_cast<std::string *>((int)(filename));
  LoadGraphic(target, *filename_s);
}

void Api::_SetTexture(Object* target,double filename){
  std::string *filename_s = reinterpret_cast<std::string *>((int)(filename));
  SetTexture(target, *filename_s);
}

void Api::_SetGraphicRect(Object* target,double sx,double sy,double dx,double dy){
  Uint32 sxi = (int)(sx);
  Uint32 syi = (int)(sy);
  Uint32 dxi = (int)(dx);
  Uint32 dyi = (int)(dy);
  SetGraphicRect(target, sxi, syi, dxi, dyi);
}

void Api::_SetGraphicAngle(Object* target,double angle){
  Uint32 anglei = (Uint32)(angle);
  SetGraphicAngle(target, anglei);
}

void Api::_DrawGraphic(Object* target,double x,double y){
  Uint32 xi = (int)(x);
  Uint32 yi = (int)(y);
  DrawGraphic(target,xi,yi);
}

/* Status*/
void Api::_SetSpeed(Object* target,double speed){
  int speedi = (int)(speed);
  SetSpeed(target, speedi);
}
void Api::_SetLife(Object* target,double life){
  int lifei = (int)(life);
  SetLife(target, lifei);
}
void Api::_SetX(Object* target,double x){
  double xi = (int)(x);
  SetX(target, xi);
}
void Api::_SetY(Object* target,double y){
  double yi = (int)(y);
  SetY(target, yi);
}
int Api::_GetPlayerX(Object* target){
  GetPlayerX(target);
}
int Api::_GetPlayerY(Object* target){
  GetPlayerY(target);
}
int Api::_GetSpeedX(Object* target){
  GetSpeedX(target);
}
int Api::_GetSpeedY(Object* target){
  GetSpeedY(target);
}
int Api::_GetX(Object* target){
  return GetX(target);
}
int Api::_GetY(Object* target){
  return GetY(target);
}
int Api::_GetMX(Object* target){
  return GetMX(target);
}
int Api::_GetMY(Object* target){
  return GetMY(target);
}
int Api::_GetW(Object* target){
  return GetW(target);
}
int Api::_GetH(Object* target){
  return GetH(target);
}
int Api::_GetCenterX(){
  return GetCenterX();
}
int Api::_GetCenterY(){
  return GetCenterY();
}

/* Danmaku */
void Api::_CreatePlayerShot01(Object* target,double x,double y,
                            double speed,double angle,double damage,
                            double pene,double id){
  int xi = (int)x;
  int yi = (int)y;
  int penei = (int)pene;
  int idi = (int)id;
  CreatePlayerShot01(target,xi,yi,speed,angle,damage,penei,idi);
}
void Api::_CreateShot01(Object* target,double x,double y,
                      double speed,double angle,double color,double delay){
  int xi = (int)x;
  int yi = (int)y;
  Bullet::Color colorc= (Bullet::Color)((int)color);
  int delayi = (int)delay;
  CreateShot01(target,xi,yi,speed,angle,colorc, delayi);
}

/* SpellCard */
void Api::_CutIn(Object* target,double label,double img,double x1,double y1,double x2,double y2){
  std::string *labelp = reinterpret_cast<std::string *>((int)(label));
  std::string *imgp = reinterpret_cast<std::string *>((int)(img));
  int x1i = (int)x1;
  int y1i = (int)y1;
  int x2i = (int)x2;
  int y2i = (int)y2;

  CutIn(target,*labelp,*imgp,x1i,y1i,x2i,y2i);
}
/* Action */
void Api::_SetMovePosition02(Object* target,double x,double y,double frame){
  int xi = (int)x;
  int yi = (int)y;
  int framei = (int)frame;
  SetMovePosition02(target,xi,yi,framei);
}

/* Keyboard */
Api::KeyState Api::_GetKeyState(double key){
  SDL_Keycode keys = (SDL_Keycode)key;
  GetKeyState(keys);
}

/* Other */
std::string Api::_GetCurrentScriptDirectory(){
  return GetCurrentScriptDirectory();
}
