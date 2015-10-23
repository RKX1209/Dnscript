#include <string>
#include <SDL.h>
#include <cstdio>
#include "Api.hpp"
#include "test/enemy_test.hpp"
#include "Enemy.hpp"
#include "Bullet.hpp"

/* Script test */
enemy_test::enemy_test(Enemy* _enemy){
  api = Api::instance();
  enemy = _enemy;
  count = 0;
  cx = api->GetCenterX();
  imgAngle = 10;
  shotAngle = 0;
}
enemy_test::~enemy_test(){
}

void enemy_test::Initialize(){
  std::string current = api->GetCurrentScriptDirectory();
  std::string imgEnemy = current + "/img/Enemy.png";
  printf("%s\n",imgEnemy.c_str());
  //std::string imgRumiaCutIn = current + "img/RumiaCutIn.png";

  api->LoadGraphic(enemy,imgEnemy);
  api->SetLife(enemy,1500);
  api->SetGraphicRect(enemy,1,1,32,32);
  api->SetTexture(enemy,imgEnemy);
  api->SetMovePosition02(enemy,cx + 0,api->GetCenterY(),30);
}
void enemy_test::MainLoop(){
  if(count % 30 == 0){
    for(int angle = 0; angle <= 360; angle += 20){
      api->CreateShot01(enemy,api->GetX(enemy),api->GetY(enemy),5,angle,Bullet::RED,3);
      //api->CreateShot01(enemy,api->GetX(enemy),api->GetY(enemy),5,angle,Bullet::YELLOW,5);
    }
  }
  count++;
}
void enemy_test::DrawLoop(){
  //api->SetGraphicAngle(enemy,imgAngle);
  //printf("(%d,%d)\n",api->GetX(enemy),api->GetY(enemy));
	api->DrawGraphic(enemy,api->GetX(enemy), api->GetY(enemy));
}
