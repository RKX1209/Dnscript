#ifndef __TEXTURE_HPP__
#define __TEXTURE_HPP__

#include <cstring>

class Texture{
private:
    GLuint tex_id; //texture id in OpenGL
    GLfloat tex_pos[2 * 4];
public:
    Texture(): tex_id(-1){};
    GLuint get_tex_id(){
      return this->tex_id;
    }
    GLuint* get_tex_idp(){
      return &tex_id;
    }
    void set_tex_id(GLuint _tex_id){
      this->tex_id = _tex_id;
    }
    void set_tex_pos(GLfloat _tex_pos[2 * 4]){
      memcpy(this->tex_pos,_tex_pos,2 * 4 * sizeof(GLfloat));
    }
    GLfloat* get_tex_pos(){
      return tex_pos;
    }
};

#endif
