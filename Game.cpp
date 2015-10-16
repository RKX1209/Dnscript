#include <cstdlib>
#include <cstdio>

#include "Api.hpp"
#include "Object.hpp"
#include "Load.hpp"
#include "Clear.hpp"
#include "Play.hpp"
#include "Menu.hpp"
#include "Game.hpp"
#include "Utility.hpp"
#include "Dnscript.hpp"

Game::Game():load(0),clear(0),play(0),menu(0){
  Api::create();
  load = new Load();
  next = SEQ_NONE;
}
Game::~Game(){
  Api::destroy();
  SAFE_DELETE(load);
  SAFE_DELETE(clear);
  SAFE_DELETE(play);
  SAFE_DELETE(menu);
}
void Game::update(Dnscript* parent){
  if(load){
    load->update(this);
  }else if(clear){
    clear->update(this);
  }else if(play){
    play->update(this);
  }else if(menu){
    menu->update(this);
  }else{
    abort();
  }
  switch(next){
    case SEQ_LOAD:
      load = new Load();
      break;
    case SEQ_CLEAR:
      SAFE_DELETE(play);
      SAFE_DELETE(menu);
      clear = new Clear();
      break;
    case SEQ_PLAY:
      SAFE_DELETE(load);
      play = new Play();
      break;
    case SEQ_MENU:
      menu = new Menu();
      break;

    default:
      break;
  }
  next = SEQ_NONE;
}
void Game::draw(void){
  if(load){
    load->draw();
  }else if(clear){
    clear->draw();
  }else if(play){
    play->draw();
  }else if(menu){
    menu->draw();
  }else{
    abort();
  }
}

void Game::load_data(void){

}
void Game::moveTo(SeqID _next){
  next = _next;
}
