#include <string>
#include "Api.hpp"
#include "Object.hpp"
#include "Keyboard.hpp"
#include "Select.hpp"
#include "Dnscript.hpp"

Select::Select(){
  Api::create();
  api = Api::instance();
  keyboard = Keyboard::instance();
  std::string filename("img/select.png");
  obj_back = new Object();
  api->LoadGraphic(obj_back,filename);
  api->SetTexture(obj_back,filename);
  SDL_Surface* image = obj_back->get_image();
  api->SetGraphicRect(obj_back,0,0,image->w,image->h);
}

Select::~Select(){
  Api::destroy();
  delete obj_back;
}

void Select::update(Dnscript* parent){
  if(keyboard->is_keyon(SDLK_SPACE)){
    keyboard->keytoggle(SDLK_SPACE);
    parent->moveTo(Dnscript::SEQ_GAME);
  }
}
void Select::draw(){
  SDL_Surface* image = obj_back->get_image();
  api->DrawGraphic(obj_back,0,0);
}
