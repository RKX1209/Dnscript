#include <cstring>
#include <iostream>
#include <cstdlib>
#include <cstdio>
#include <GL/glut.h>
#include <GL/freeglut.h>
#include <png++/png.hpp>
#include "Image.hpp"

void Image::load_graphic(std::string _filename){
  this->filename = _filename;
  size_t dot = 0;
  try{
    dot = filename.find(".");
    if(dot != std::string::npos){
      std::string ext = filename.substr(dot + 1);
      //printf("%s\n",ext.c_str());
      if(ext == "png"){
        this->__load_graphic_png();
      }else{
        throw "[*ERROR*] Image::load_graphic image format not supported";
      }
    }else{
      throw "[*ERROR*] Image::load_graphic file extension not found";
    }
   }catch(char *error){
     printf("%s\n",error);
     abort();
   }
}

void Image::__load_graphic_png(){
  try{
    png::image <png::rgba_pixel> image(this->filename);
    this->width = image.get_width();
    this->height = image.get_height();
    this->img_buff.resize(this->width * this->height * 3);
    //printf("%d x %d\n",this->width,this->height);
    for (size_t y = 0; y < this->height; ++y) {
      for (size_t x = 0; x < this->width; ++x){
        this->img_buff[y * 3 * width + x * 3 + 0] = (char)image[y][x].red;
        this->img_buff[y * 3 * width + x * 3 + 1] = (char)image[y][x].green;
        this->img_buff[y * 3 * width + x * 3 + 2] = (char)image[y][x].blue;
      }
    }
/*    for (size_t y = 0; y < this->height / 100; ++y) {
      for (size_t x = 0; x < this->width; ++x){
        printf("(0x%08x,0x%08x,0x%08x)",this->img_buff[y * 3 * width + x * 3 + 0],
                      this->img_buff[y * 3 * width + x * 3 + 1],
                      this->img_buff[y * 3 * width + x * 3 + 2]);
      }
    }*/

  }catch(png::error& error){
    printf("%s\n",error.what());
    abort();
  }
  printf("%s\n",this->filename.c_str());
}
