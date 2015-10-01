#include <GL/gl.h>
#include <GL/glut.h>
#include <GL/glu.h>
#include <GL/freeglut.h>
#include <cstdlib>
#include <cstdio>

#include "Api.hpp"
#include "Object.hpp"
#include "Select.hpp"
#include "Title.hpp"
#include "Game.hpp"
#include "Dnscript.hpp"
#include "Utility.hpp"

Dnscript::Dnscript():title(0),select(0),game(0){  
  title = new Title();
  next = SEQ_NONE;
}
Dnscript::~Dnscript(){
  SAFE_DELETE(title);
  SAFE_DELETE(select);
  SAFE_DELETE(game);
}
void Dnscript::update(void){
  if(title){
    title->update(this);
  }else if(select){
    select->update(this);
  }else if(game){
    game->update(this);
  }else{
    abort();
  }
  switch(next){
    case SEQ_TITLE:
      SAFE_DELETE(select);
      SAFE_DELETE(game);
      title = new Title();
      break;
    case SEQ_STAGE_SELECT:
      SAFE_DELETE(title);
      SAFE_DELETE(game);
      select = new Select();
      break;
    case SEQ_GAME:
      SAFE_DELETE(title);
      SAFE_DELETE(select);
      game = new Game();
      break;
    default:
      break;
  }
  next = SEQ_NONE;
}
void Dnscript::draw(void){
  if(title){
    title->draw();
  }else if(select){
    select->draw();
  }else if(game){
    game->draw();
  }else{
    abort();
  }
}
