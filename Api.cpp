#include <iostream>
#include <GL/glut.h>
#include <GL/freeglut.h>
#include "Texture.hpp"
#include "Image.hpp"
#include "Character.hpp"
#include "Api.hpp"

Api* Api::mInstance = 0;

Api* Api::instance(){
    return mInstance;
}

void Api::create(){
  try{
    if(mInstance) throw "[*ERROR*] Api::create() cannnot create instance twice";
    mInstance = new Api();
  }catch(char *error){
    std::cerr << error << "\n";
    abort();
  }
}

void Api::destroy(){
  delete mInstance;
}

/* ### API list ### */
void Api::LoadGraphic(Character* target,char* filename){
  target->get_image()->load_graphic(filename);
}
void Api::SetTexture(Character* target,char* filename){
  glGenTextures(1, target->get_texture()->get_tex_idp());
  glBindTexture(GL_TEXTURE_2D, target->get_texture()->get_tex_id());
  glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA,
                target->get_image()->get_width(),
                target->get_image()->get_height(),
                0, GL_RGBA, GL_UNSIGNED_BYTE, target->get_image()->get_buff());

}
void Api::SetGraphicRect(Character* target,int sx,int sy,int dx,int dy){

}
