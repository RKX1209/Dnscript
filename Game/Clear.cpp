#include <string>
#include "Api.hpp"
#include "Object.hpp"
#include "Keyboard.hpp"
#include "Clear.hpp"
#include "Game.hpp"

Clear::Clear(){
  api = Api::instance();
  keyboard = Keyboard::instance();
  std::string filename("img/Clear.png");
  obj_back = new Object();
  api->LoadGraphic(obj_back,filename);
  api->SetTexture(obj_back,filename);
  SDL_Surface* image = obj_back->get_image();
  api->SetGraphicRect(obj_back,0,0,image->w,image->h);
}

Clear::~Clear(){
  delete obj_back;
}

void Clear::update(Game* parent){
}
void Clear::draw(){
  SDL_Surface* image = obj_back->get_image();
  api->DrawGraphic(obj_back,0,0);
}
