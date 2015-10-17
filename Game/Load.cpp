#include <string>
#include "Api.hpp"
#include "Object.hpp"
#include "Keyboard.hpp"
#include "Load.hpp"
#include "Game.hpp"

Load::Load(){
  api = Api::instance();
  keyboard = Keyboard::instance();
  std::string filename("img/load.png");
  loading = false;
  obj_back = new Object();
  api->LoadGraphic(obj_back,filename);
  api->SetTexture(obj_back,filename);
  SDL_Surface* image = obj_back->get_image();
  api->SetGraphicRect(obj_back,0,0,image->w,image->h);
}

Load::~Load(){
  delete obj_back;
}

void Load::update(Game* parent){
  static int count;
  if(!loading){
    parent->load_data();
    loading = true;
  }else if(count >= 10){
    parent->moveTo(Game::SEQ_PLAY);
  }
  ++count;
}

void Load::draw(){
  api->RenderClear();
  api->DrawGraphic(obj_back,0,0);
  api->RenderPresent();
}
