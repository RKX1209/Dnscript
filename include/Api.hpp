#ifndef __API_HPP__
#define __API_HPP__

#include <string>
#include <SDL.h>
#include <SDL_image.h>

/* ### Singleton class ### */
class Object;
class Keyboard;
class Api{
public:
  enum KeyState{
    KEY_PUSH,
    KEY_HOLD,
    KEY_RELEASE,
  };
private:
  Api();
  ~Api(){;}
  Api(const Api&){;}
  static Api* mInstance;
  Keyboard* keyboard;
public:
  static Api* instance();
  static void create();
  static void destroy();

  /* Graphic */
  void LoadGraphic(Object*,std::string);
  void SetTexture(Object*,std::string);
  void SetGraphicRect(Object*,Uint32,Uint32,Uint32,Uint32);
  void SetGraphicPos(Object*,Uint32,Uint32,Uint32,Uint32);
  void DrawGraphic(Object*,Uint32,Uint32);

  /* Status */
  void SetSpeed(Object*,int);
  void SetLife(Object*,int);
  void SetX(Object*,int);
  void SetY(Object*,int);
  int GetPlayerX(Object*);
  int GetPlayerY(Object*);

  /* Danmaku */
  void CreatePlayerShot01(Object*,int,int,double,double,double,int,int);
  void CreateShot01(Object*,int,int,double,double,int,int);
  /* Action */
  void SetMovePosition02(Object*,int,int,int);
  /* Keyboard */
  KeyState GetKeyState(SDL_Keycode);
  /* Other */
  std::string GetCurrentScriptDirectory();
  /* Unofficial API (hidden) */
  void RenderClear();
  void RenderPresent();
};

#endif
