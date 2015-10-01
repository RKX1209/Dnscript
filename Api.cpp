#include <iostream>
#include <string>
#include <cstdio>
#include <GL/glut.h>
#include <GL/freeglut.h>
#include "Texture.hpp"
#include "Image.hpp"
#include "Object.hpp"
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
void Api::LoadGraphic(Object* target,std::string filename){
  target->get_image()->load_graphic(filename);
}

void Api::SetTexture(Object* target,std::string filename){
  GLuint tex_id;
  //glGenTextures(1, target->get_texture()->get_tex_idp());
  glGenTextures(1,&tex_id);
  printf("%d\n",tex_id);
  /*GLenum errCode = glGetError();
  printf("%s\n",gluErrorString(errCode));  */
  target->get_texture()->set_tex_id(tex_id);
  glBindTexture(GL_TEXTURE_2D, target->get_texture()->get_tex_id());
  glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA,
                target->get_image()->get_width(),
                target->get_image()->get_height(),
                0, GL_RGBA, GL_UNSIGNED_BYTE, target->get_image()->get_buff());
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

}

void Api::SetGraphicRect(Object* target,GLfloat sx,GLfloat sy,GLfloat dx,GLfloat dy){
  GLfloat width = dx - sx;
  GLfloat height = dy - sy;
  target->set_width(width);
  target->set_height(height);
  Image *image = target->get_image();
  GLfloat texuv[] = {
    sx / image->get_width(),dy / image->get_height(),
    dx / image->get_width(),dy / image->get_height(),
    dx / image->get_width(),sy / image->get_height(),
    sx / image->get_width(),sy / image->get_height(),
  };
  glTexCoordPointer(2, GL_FLOAT, 0, texuv); //Set texture position
  target->get_texture()->set_tex_pos(texuv);
}

void Api::DrawGraphic(Object* target,GLfloat x,GLfloat y){
  target->set_pos(x,y);
  GLfloat vtx[] = {
    x - target->get_width() / 2, y - target->get_height() / 2,
    x + target->get_width() / 2, y - target->get_height() / 2,
    x + target->get_width() / 2, y + target->get_height() / 2,
    x - target->get_width() / 2, y + target->get_height() / 2,
  };
  glVertexPointer(2, GL_FLOAT, 0, vtx); //Set draw position
  glTexCoordPointer(2, GL_FLOAT, 0, target->get_texture()->get_tex_pos()); //Set texture position
  glBindTexture(GL_TEXTURE_2D, target->get_texture()->get_tex_id());
  //printf("tex_id: %d\n",target->get_texture()->get_tex_id());
  /* Draw */
  glEnable(GL_TEXTURE_2D);
  glEnableClientState(GL_VERTEX_ARRAY);
  glEnableClientState(GL_TEXTURE_COORD_ARRAY);
  glDrawArrays(GL_QUADS, 0, 4);
  glDisableClientState(GL_TEXTURE_COORD_ARRAY);
  glDisableClientState(GL_VERTEX_ARRAY);
  glDisable(GL_TEXTURE_2D);
}
