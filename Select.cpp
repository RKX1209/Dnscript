#include <string>
#include "Api.hpp"
#include "Object.hpp"
#include "Select.hpp"
#include "Dnscript.hpp"

Select::Select(){
  Api::create();
  api = Api::instance();
  std::string filename = "img/select.png";
  obj_back = new Object();
  SDL_Surface* image = obj_back->get_image();
  api->LoadGraphic(obj_back,filename);
  api->SetTexture(obj_back,filename);
  api->SetGraphicRect(obj_back,0,0,image->w,image->h);
}

Select::~Select(){
  Api::destroy();
  delete obj_back;
}

void Select::update(Dnscript* parent){
}
void Select::draw(){
  SDL_Surface* image = obj_back->get_image();
  api->DrawGraphic(obj_back,image->w / 2,image->h / 2);
}
