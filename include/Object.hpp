#ifndef __OBJECT_HPP__
#define __OBJECT_HPP__

#include <SDL.h>

class Texture;
class Object{
private:
  SDL_Surface* image;
  SDL_Texture* texture;
protected:
  SDL_Rect* obj_rect;
  SDL_Rect* obj_pos;
  int x;
  int y;
  int w;
  int h;
public:
  Object() : x(0),y(0){
    obj_rect = new SDL_Rect;
    obj_pos = new SDL_Rect;
  }
  ~Object(){
    delete obj_rect;
    delete obj_pos;
    SDL_FreeSurface(image);
    SDL_DestroyTexture(texture);
  }
  SDL_Surface* get_image(){ return this->image; }
  void set_image(SDL_Surface *_image){ this->image = _image; }

  SDL_Texture* get_texture(){ return this->texture; }
  void set_texture(SDL_Texture *_tex){ this->texture = _tex; }

  SDL_Rect* get_obj_rect(){ return this->obj_rect; }
  void set_obj_rect(Uint32 _x,Uint32 _y,Uint32 _w,Uint32 _h){
    obj_rect->x = _x;
    obj_rect->y = _y;
    obj_rect->w = _w;
    obj_rect->h = _h;
  }
  SDL_Rect* get_obj_pos(){ return this->obj_pos; }
  void set_obj_pos(Uint32 _x,Uint32 _y){
    obj_pos->x = _x;
    obj_pos->y = _y;
    obj_pos->w = obj_rect->w;
    obj_pos->h = obj_rect->h;
  }
  virtual void shoot(int,int,double,double,double,int,int){}
  virtual void set_x(int){}
  virtual void set_y(int){}
  virtual int get_x(){ return x; }
  virtual int get_y(){ return y; }
  virtual void set_speed(int){}
  virtual void set_life(int){}
  virtual void set_bomb_num(int){}
  virtual void set_graze(int){}
};

#endif
