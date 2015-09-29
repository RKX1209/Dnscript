#ifndef __CHARACTER_HPP__
#define __CHARACTER_HPP__

class Texture;
class Image;
class Character{
private:
  Texture* texture;
  Image* image;
public:
  Character():texture(0),image(0){;}
  Texture* get_texture(){
    return this->texture;
  }
  Image* get_image(){
    return this->image;
  }
};

#endif
