#include <iostream>
#include <string>
#include <cstdio>
#include "Object.hpp"
#include "Api.hpp"
#include "Dnscript.hpp"
#include "Window.hpp"

Api* Api::mInstance = 0;

Api* Api::instance(){
    return mInstance;
}

void Api::create(){
  try{
    if(mInstance) throw "[*ERROR*] Api::create() cannnot create instance twice";
    mInstance = new Api();
  }catch(char *error){
    fprintf(stderr,"%s\n",error);
    abort();
  }
}

void Api::destroy(){
  delete mInstance;
}

/* ### API list ### */
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

void Api::DrawGraphic(Object* target,Uint32 x,Uint32 y){
  target->set_obj_pos(x,y);
  SDL_Renderer* renderer = Window::renderer;
  SDL_RenderClear(renderer);
  SDL_RenderCopy(renderer, target->get_texture(), nullptr, nullptr);
  SDL_RenderPresent(renderer);
}
