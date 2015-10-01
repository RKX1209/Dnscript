#ifndef __OBJECT_HPP__
#define __OBJECT_HPP__

class Texture;
class Image;
class Object{
private:
  Texture* texture;
  Image* image;
protected:
  /* Object's pos and size. **NOT** image's but Object's.
     Image's staus is owned by Image class itself. */
  GLfloat pos_x;
  GLfloat pos_y;
  GLfloat width;
  GLfloat height;
public:
  Object();
  ~Object();
  GLfloat get_pos_x(){ return this->pos_x; }
  GLfloat get_pos_y(){ return this->pos_y; }
  void set_pos(GLfloat _x,GLfloat _y){ this->pos_x = _x; this->pos_y = _y; }
  GLfloat get_width(){ return this->width; }
  GLfloat get_height(){ return this->height; }
  void set_width(GLfloat _w){ this->width = _w; }
  void set_height(GLfloat _h){ this->height = _h; }
  Texture* get_texture(){ return this->texture; }
  Image* get_image(){ return this->image; }
};

#endif
