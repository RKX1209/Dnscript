#include <iostream>
#include <SDL.h>
#include "Keyboard.hpp"

Keyboard* Keyboard::mInstance = 0;

Keyboard* Keyboard::instance(){
    return mInstance;
}

void Keyboard::create(){
  try{
    if(mInstance) throw "[*ERROR*] Keyboard::create() cannnot create instance twice";
    mInstance = new Keyboard();
  }catch(char *error){
    fprintf(stderr,"%s\n",error);
	  abort();
  }
}

void Keyboard::destroy(){
  delete mInstance;
}

bool Keyboard::is_keyon(SDL_Keycode key){
  if(keys.find( key ) == keys.end()) return false;
  return keys[key] == KEY_PUSH;
}

bool Keyboard::is_keyoff(SDL_Keycode key){
  return keys[key] == KEY_RELEASE;
}

void Keyboard::keyon(SDL_Keycode key){
  if(keys[key] != KEY_TOGGLE)
    keys[key] = KEY_PUSH;
}

void Keyboard::keyoff(SDL_Keycode key){
  keys[key] = KEY_RELEASE;
}
void Keyboard::keytoggle(SDL_Keycode key){
  keys[key] = KEY_TOGGLE;
}
