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
  void LoadGraphic(Object*,std::string);
  void SetTexture(Object*,std::string);
  void SetGraphicRect(Object*,Uint32,Uint32,Uint32,Uint32);
  void DrawGraphic(Object*,Uint32,Uint32);
  void CreatePlayerShot01(Object*,int,int,double,double,double,int,int);
  void CreateShot01(Object*,int,int,double,double,int,int);
  void SetMovePosition02(Object*,int,int,int);
};

#endif
