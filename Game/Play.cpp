#include <string>
#include "Api.hpp"
#include "Object.hpp"
#include "Keyboard.hpp"
#include "Play.hpp"
#include "Game.hpp"
#include "Window.hpp"
#include "Player.hpp"

#include "test/player_test.hpp"

Play::Play(){
  api = Api::instance();
  keyboard = Keyboard::instance();
  std::string filename("img/play.jpg");
  obj_back = new Object();
  api->LoadGraphic(obj_back,filename);
  api->SetTexture(obj_back,filename);
  SDL_Surface* image = obj_back->get_image();
  api->SetGraphicRect(obj_back,0,0,image->w,image->h);
  player = new Player();
  p_test = new player_test(player);
  p_test->Initialize();
}

Play::~Play(){
  delete obj_back;
  delete player;
  delete p_test;
}

void Play::update(Game* parent){
  player->update();
  p_test->MainLoop();
}
void Play::draw(){
  api->RenderClear();
  api->DrawGraphic(obj_back,0,0);
  player->draw();
  p_test->DrawLoop();
  api->RenderPresent();
}

bool Play::in_monitor(int x,int y){
  return 0 <= x && x < Window::win_rect.w && 0 <= y && y <= Window::win_rect.h;
}
