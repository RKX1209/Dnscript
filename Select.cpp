#include <string>
#include <GL/glut.h>
#include <GL/freeglut.h>
#include "Api.hpp"
#include "Image.hpp"
#include "Object.hpp"
#include "Select.hpp"
#include "Dnscript.hpp"

Select::Select(){
  Api::create();
  api = Api::instance();
  std::string filename = "img/select.png";
  obj_back = new Object();
  Image* image = obj_back->get_image();
  api->LoadGraphic(obj_back,filename);
  api->SetTexture(obj_back,filename);
  api->SetGraphicRect(obj_back,0,0,image->get_width(),image->get_height());
}

Select::~Select(){
  Api::destroy();
  delete obj_back;
}

void Select::update(Dnscript* parent){
}
void Select::draw(){
  Image* image = obj_back->get_image();
  api->DrawGraphic(obj_back,image->get_width() / 2,image->get_height() / 2);
}
