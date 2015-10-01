#include <string>
#include <GL/glut.h>
#include <GL/freeglut.h>
#include "Api.hpp"
#include "Image.hpp"
#include "Object.hpp"
#include "Title.hpp"
#include "Dnscript.hpp"

Title::Title(){
  Api::create();
  api = Api::instance();
  obj_back = new Object();
  std::string filename("img/select.png");
  Image* image = obj_back->get_image();
  api->LoadGraphic(obj_back,filename);
  api->SetTexture(obj_back,filename);
  api->SetGraphicRect(obj_back,0,0,image->get_width(),image->get_height());
}

Title::~Title(){
  Api::destroy();
  delete obj_back;
}

void Title::update(Dnscript *parent){
}

void Title::draw(){
  Image* image = obj_back->get_image();
  //printf("%d x %d\n",image->get_width(),image->get_height());
  api->DrawGraphic(obj_back,image->get_width() / 2,image->get_height() / 2);
}
