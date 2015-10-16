#include <string>
#include "Api.hpp"
#include "Object.hpp"
#include "Keyboard.hpp"
#include "Menu.hpp"
#include "Game.hpp"

Menu::Menu(){
  api = Api::instance();
  keyboard = Keyboard::instance();
  std::string filename("img/menu.png");
  obj_back = new Object();
  api->LoadGraphic(obj_back,filename);
  api->SetTexture(obj_back,filename);
  SDL_Surface* image = obj_back->get_image();
  api->SetGraphicRect(obj_back,0,0,image->w,image->h);
}

Menu::~Menu(){
  delete obj_back;
}

void Menu::update(Game* parent){
}
void Menu::draw(){
  SDL_Surface* image = obj_back->get_image();
  api->DrawGraphic(obj_back,0,0);
}
