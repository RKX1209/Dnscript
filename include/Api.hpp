#ifndef __API_HPP__
#define __API_HPP__

#include <string>
#include <SDL.h>
#include <SDL_image.h>

/* ### Singleton class ### */
class Object;
class Api{
private:
  Api(){;}
  ~Api(){;}
  Api(const Api&){;}
  static Api* mInstance;
public:
  static Api* instance();
  static void create();
  static void destroy();
  void LoadGraphic(Object* target,std::string filename);
  void SetTexture(Object* target,std::string filename);
  void SetGraphicRect(Object* target,Uint32 sx,Uint32 sy,Uint32 dx,Uint32 dy);
  void DrawGraphic(Object* target,Uint32 x,Uint32 y);
};

#endif
