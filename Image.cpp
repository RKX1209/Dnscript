#include <cstring>
#include <iostream>
#include <cstdlib>
#include <GL/glut.h>
#include <GL/freeglut.h>
#include <png++/png.hpp>
#include "Image.hpp"

void Image::load_graphic(char* _filename){
  this->filename = _filename;
  char *dot;
  try{
    if((dot = strstr(this->filename,".")) != NULL){
      const char *ext = ++dot;
      if(strcmp(ext,"png") == 0){
        this->__load_graphic_png();
      }else{
        throw "[*ERROR*] Image::load_graphic image format not supported";
      }
    }else{
      throw "[*ERROR*] Image::load_graphic file extension not found";
    }
   }catch(char *error){
     std::cerr << error << "\n";
     abort();
   }
}

void Image::__load_graphic_png(){
  try{
    png::image <png::rgba_pixel> image(this->filename);
    this->width = image.get_width();
    this->height = image.get_height();
    this->img_buff.resize(this->width * this->height * 3);
    for (size_t y = 0; y < this->height; ++y) {
      for (size_t x = 0; x < this->width; ++x){
        this->img_buff[y * 3 * width + x * 3 + 0] = (char)image[y][x].red;
        this->img_buff[y * 3 * width + x * 3 + 1] = (char)image[y][x].green;
        this->img_buff[y * 3 * width + x * 3 + 2] = (char)image[y][x].blue;
      }
    }
  }catch(png::error& error){
    std::cerr << error.what() << "\n";
    abort();
  }
}
