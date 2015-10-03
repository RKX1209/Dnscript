#include <string>
#include "Api.hpp"
#include "Object.hpp"
#include "Title.hpp"
#include "Dnscript.hpp"

Title::Title(){
  Api::create();
  api = Api::instance();
  obj_back = new Object();
  std::string filename("img/select.png");
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
}

void Title::draw(){
  SDL_Surface* image = obj_back->get_image();
  //printf("%d x %d\n",image->w,image->h);
  api->DrawGraphic(obj_back,0,0);
}
