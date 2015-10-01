#include <iostream>
#include <map>
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
    std::cerr << error << "\n";
    abort();
  }
}

void Keyboard::destroy(){
  delete mInstance;
}

bool Keyboard::is_keyon(unsigned char key){
  return keys[key] == KEY_PUSH;
}

bool Keyboard::is_keyoff(unsigned char key){
  return keys[key] == KEY_RELEASE;
}
