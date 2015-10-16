#ifndef __EVENT_HPP__
#define __EVENT_HPP__

#include <SDL.h>
/* ### Singleton class ### */
class Event{
private:
  SDL_Event event;
  Event(){;}
  ~Event(){;}
  Event(const Event&){;}
  static Event* mInstance;
public:
  static Event* instance();
  static void create();
  static void destroy();
  void set_event(SDL_Event _ev){ event = _ev; }
  SDL_Event get_event(){ return event; }
  SDL_Keycode get_keycode(){ return event.key.keysym.sym; }
};

#endif
