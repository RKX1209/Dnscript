#ifndef __KEYBOARD_HPP__
#define __KEYBOARD_HPP__

#include <map>

/* ### Singleton class ### */
class Keyboard{
private:
  enum State{
    KEY_PUSH,
    KEY_RELEASE,
    KEY_TOGGLE
  };
  std::map<SDL_Keycode,State> keys;
  Keyboard(){;}
  ~Keyboard(){;}
  Keyboard(const Keyboard&){;}
  static Keyboard* mInstance;
public:
  bool is_keyon(SDL_Keycode key);
  bool is_keyoff(SDL_Keycode key);
  bool is_keytoggle(SDL_Keycode key);
  void keyon(SDL_Keycode key);
  void keyoff(SDL_Keycode key);
  void keytoggle(SDL_Keycode key);
  static Keyboard* instance();
  static void create();
  static void destroy();

};

#endif
