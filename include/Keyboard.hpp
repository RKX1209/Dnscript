#ifndef __KEYBOARD_HPP__
#define __KEYBOARD_HPP__

/* ### Singleton class ### */
class Keyboard{
private:
  enum State{
    KEY_PUSH,
    KEY_RELEASE
  };
  std::map<unsigned char,State> keys;
  Keyboard(){;}
  ~Keyboard(){;}
  Keyboard(const Keyboard&){;}
  static Keyboard* mInstance;
public:
  bool is_keyon(unsigned char key);
  bool is_keyoff(unsigned char key);
  static Keyboard* instance();
  static void create();
  static void destroy();

};

#endif
