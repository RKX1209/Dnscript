#ifndef __IMAGE_HPP__
#define __IAMGE_HPP__

#include <vector>

class Image{
private:
  std::vector<char>img_buff;
  int width;
  int height;
  GLfloat img_pos[2 * 4];
  char* filename;
public:
  Image():width(0),height(0),filename(0){;}
  void load_graphic(char* _filename);
  void __load_graphic_png();
  GLvoid* get_buff(){
    return &(this->img_buff[0]);
  }
  int get_width(){
    return this->width;
  }
  int get_height(){
    return this->height;
  }
};

#endif
