#include <string>
#include <SDL.h>
#include <cstdio>
#include "Api.hpp"
#include "test/player_test.hpp"
#include "Player.hpp"

/* Script test */
player_test::player_test(Player* _player){
  api = Api::instance();
  player = _player;
}
player_test::~player_test(){
}

void player_test::Initialize(){
  shotCount = -1;
  bNextShot = false;
  std::string current = api->GetCurrentScriptDirectory();
  std::string imgRumia = current + "/img/Reimu.png";
  printf("%s\n",imgRumia.c_str());
  //std::string imgRumiaCutIn = current + "img/RumiaCutIn.png";

  api->LoadGraphic(player,imgRumia);
  api->SetSpeed(player,10);
  api->SetTexture(player,imgRumia);
}
void player_test::MainLoop(){
  if((api->GetKeyState(SDLK_z) == Api::KEY_PUSH ||
      api->GetKeyState(SDLK_z) == Api::KEY_HOLD || bNextShot==true)
      && shotCount==-1){
  			shotCount = 0;
  			bNextShot = false;
  }
  if(api->GetKeyState(SDLK_x) == Api::KEY_PUSH ||
    api->GetKeyState(SDLK_x) == Api::KEY_HOLD){
      this->SpellCard();
  }
  if(api->GetKeyState(SDLK_z) == Api::KEY_HOLD && shotCount>0){
  			bNextShot = true;
  }
  if(shotCount % 5 == 0){
    api->CreatePlayerShot01(player,api->GetPlayerX(player), api->GetPlayerY(player), 15, 255, 1.3, 1, 1);
  	api->CreatePlayerShot01(player,api->GetPlayerX(player), api->GetPlayerY(player), 15, 265, 1.5, 2, 1);
  	api->CreatePlayerShot01(player,api->GetPlayerX(player), api->GetPlayerY(player), 15, 270, 1.7, 3, 1);
  	api->CreatePlayerShot01(player,api->GetPlayerX(player), api->GetPlayerY(player), 15, 275, 1.5, 2, 1);
  	api->CreatePlayerShot01(player,api->GetPlayerX(player), api->GetPlayerY(player), 15, 285, 1.3, 1, 1);
  }
  if(shotCount >= 0){
  	shotCount++;
  }
  if(shotCount == 30){
  	shotCount=-1;
  }
}
void player_test::SpellCard(){
  std::string current = api->GetCurrentScriptDirectory();
  api->CutIn(player,"Test",current + "/img/CutinReimu.png",0,0,256,256);
}

void player_test::DrawLoop(){
  if(api->GetKeyState(SDLK_LEFT) == Api::KEY_PUSH || api->GetKeyState(SDLK_LEFT) == Api::KEY_HOLD){
    api->SetGraphicRect(player,1, 51, 50, 100);
	}else if(api->GetKeyState(SDLK_RIGHT) == Api::KEY_PUSH || api->GetKeyState(SDLK_RIGHT) == Api::KEY_HOLD){
		api->SetGraphicRect(player,1, 101, 50, 150);
	}else {
		api->SetGraphicRect(player,1, 1, 50, 50);
	}
  //printf("(%d,%d)\n",api->GetPlayerX(player),api->GetPlayerY(player));
	api->DrawGraphic(player,api->GetPlayerX(player), api->GetPlayerY(player));
}
