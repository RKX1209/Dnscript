#include <string>
#include "Api.hpp"
#include "Object.hpp"
#include "Game.hpp"
#include "Dnscript.hpp"

Game::Game(){
  Api::create();
  api = Api::instance();
  /*const char *filename = "img/Game.png";
  obj_back = new Object();
  api->LoadGraphic(obj_back,filename);
  api->SetTexture(obj_back,filename);
  api->SetGraphicRect(obj_back,0,0,image->get_width,image->get_height); */
}

Game::~Game(){
  Api::destroy();
}

void Game::update(Dnscript* parent){
}
void Game::draw(){}
