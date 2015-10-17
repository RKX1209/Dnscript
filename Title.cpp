#include <string>
#include <SDL.h>
#include "Api.hpp"
#include "Event.hpp"
#include "Object.hpp"
#include "Keyboard.hpp"
#include "Title.hpp"
#include "Dnscript.hpp"

Title::Title(){
  Api::create();
  api = Api::instance();
  keyboard = Keyboard::instance();
  obj_back = new Object();
  std::string filename("img/title.png");
  api->LoadGraphic(obj_back,filename);
  api->SetTexture(obj_back,filename);
  SDL_Surface* image = obj_back->get_image();
  api->SetGraphicRect(obj_back,0,0,image->w,image->h);
}

Title::~Title(){
  Api::destroy();
  delete obj_back;
}

void Title::update(Dnscript *parent){
  if(keyboard->is_keyon(SDLK_SPACE)){
    keyboard->keytoggle(SDLK_SPACE);
    parent->moveTo(Dnscript::SEQ_STAGE_SELECT);
  }
}

void Title::draw(){
  api->RenderClear();
  api->DrawGraphic(obj_back,0,0);
  api->RenderPresent();  
}
