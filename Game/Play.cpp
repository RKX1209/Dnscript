#include <string>
#include <fstream>
#include <iostream>
#include <map>
#include <vector>
#include <list>
#include "Api.hpp"
#include "Object.hpp"
#include "Keyboard.hpp"
#include "Enemy.hpp"
#include "Play.hpp"
#include "Game.hpp"
#include "Window.hpp"
#include "Player.hpp"
#include "test/player_test.hpp"
#include "test/enemy_test.hpp"
SDL_Rect Play::win_rect;

Play::Play(){
  api = Api::instance();
  keyboard = Keyboard::instance();
  Play::win_rect.x = 20;
  Play::win_rect.y = 10;
  Play::win_rect.w = Window::win_rect.w / 4 * 3;
  Play::win_rect.h = Window::win_rect.h / 12 * 11;

  std::string filename("img/play.jpg");
  obj_back = new Object();
  api->LoadGraphic(obj_back,filename);
  api->SetTexture(obj_back,filename);
  SDL_Surface* image = obj_back->get_image();
  api->SetGraphicRect(obj_back,0,0,image->w,image->h);

  player = new Player();
  p_test = new player_test(player);
  p_test->Initialize();
  enemies.push_back(new Enemy());

  /* Compile the script code and execute @Initialize function */
  interp = new Dnlang::Interprter(enemies.front(), "Dnlang/sample/enemy.dn");
  interp->compile();
  interp->_Init();
  interp->Initialize();
  std::cout<<"enemy_0"<<enemies.front()<<std::endl;
  //e_test = new enemy_test(enemies.front());
  //e_test->Initialize();



}

Play::~Play(){
  delete obj_back;
  delete player;
  delete p_test;
  //delete e_test;
  while(!enemies.empty()){
    Enemy* e = enemies.front();
    delete e;
    enemies.pop_front();
  }
  delete interp;
}

void Play::update(Game* parent){
  player->update();
  p_test->MainLoop();
  for(int i = 0; i < enemies.size(); i++){
    enemies[i]->update();
  }
  //e_test->MainLoop();
  interp->MainLoop();
}
void Play::draw(){
  api->RenderClear();
  api->DrawGraphic(obj_back,Play::win_rect.x,Play::win_rect.y);
  player->draw();
  p_test->DrawLoop();
  for(int i = 0; i < enemies.size(); i++){
    enemies[i]->draw();
  }
  //e_test->DrawLoop();
  interp->DrawLoop();
  api->RenderPresent();
}

bool Play::in_monitor(int x,int y){
  return win_rect.x <= x && x < win_rect.w && win_rect.y <= y && y <= win_rect.h;
}
