#include <GL/glut.h>
#include <GL/freeglut.h>

#include "Image.hpp"
#include "Texture.hpp"
#include "Object.hpp"

Object::Object():texture(0),image(0){
  image = new Image();
  texture = new Texture();
}
Object::~Object(){
  delete image;
  delete texture;
}
