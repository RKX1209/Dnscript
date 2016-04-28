#ifndef __API_HPP__
#define __API_HPP__

#include <string>
#include <SDL.h>
#include <SDL_image.h>
#include "Bullet.hpp"
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
  //void SetGraphicPos(Object*,Uint32,Uint32,Uint32,Uint32);
  void SetGraphicAngle(Object*,Uint32);
  void DrawGraphic(Object*,Uint32,Uint32);

  /* Status */
  void SetSpeed(Object*,int);
  void SetLife(Object*,int);
  void SetX(Object*,int);
  void SetY(Object*,int);
  int GetPlayerX(Object*);
  int GetPlayerY(Object*);
  int GetSpeedX(Object*);
  int GetSpeedY(Object*);
  int GetX(Object*);
  int GetY(Object*);
  int GetMX(Object*);
  int GetMY(Object*);
  int GetW(Object*);
  int GetH(Object*);
  int GetCenterX();
  int GetCenterY();

  /* Danmaku */
  void CreatePlayerShot01(Object*,int,int,double,double,double,int,int);
  void CreateShot01(Object*,int,int,double,double,Bullet::Color,int);
  /* SpellCard */
  void CutIn(Object*,std::string,std::string,int,int,int,int);
  /* Action */
  void SetMovePosition02(Object*,int,int,int);
  /* Keyboard */
  KeyState GetKeyState(SDL_Keycode);
  /* Other */
  std::string GetCurrentScriptDirectory();
  /* Unofficial API (hidden) */
  void RenderClear();
  void RenderPresent();

  /* ####### ABI (interface to Dnlang) ####### */
  /* Graphic */
  void _LoadGraphic(Object*,double);
  void _SetTexture(Object*,double);
  void _SetGraphicRect(Object*,double,double,double,double);
  void _SetGraphicPos(Object*,double,double,double,double);
  void _SetGraphicAngle(Object*,double);
  void _DrawGraphic(Object*,double,double);

  /* Status */
  void _SetSpeed(Object*,double);
  void _SetLife(Object*,double);
  void _SetX(Object*,double);
  void _SetY(Object*,double);
  int _GetPlayerX(Object*);
  int _GetPlayerY(Object*);
  int _GetSpeedX(Object*);
  int _GetSpeedY(Object*);
  int _GetX(Object*);
  int _GetY(Object*);
  int _GetMX(Object*);
  int _GetMY(Object*);
  int _GetW(Object*);
  int _GetH(Object*);
  int _GetCenterX();
  int _GetCenterY();

  /* Danmaku */
  void _CreatePlayerShot01(Object*,double,double,double,double,double,double,double);
  void _CreateShot01(Object*,double,double,double,double,double,double);
  /* SpellCard */
  void _CutIn(Object*,double,double,double,double,double,double);
  /* Action */
  void _SetMovePosition02(Object*,double,double,double);
  /* Keyboard */
  KeyState _GetKeyState(double);
  /* Other */
  std::string _GetCurrentScriptDirectory();

};

#endif
