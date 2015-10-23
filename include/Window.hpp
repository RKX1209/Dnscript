#ifndef __WINDOW_HPP__
#define __WINDOW_HPP__

#include <SDL.h>
#include "Event.hpp"
#include "Keyboard.hpp"
#include "Dnscript.hpp"
#include "Frame.hpp"

class Window{
public:
  static SDL_Window* window;
  static SDL_Renderer* renderer;
  static SDL_Rect win_rect;
  static const char* win_title;
  static const double fps;
  static const int timer_wait_mil;
  static Dnscript* dnscript;
  static Event* event;
  static Keyboard* keyboard;
  static Frame* frame;

  Window(void) { ; }

  static void init(void){
    try{
        if( SDL_Init(SDL_INIT_EVERYTHING) < 0 ) throw "[*ERROR*] Window::main SDL_Init fail";
        SDL_CreateWindowAndRenderer(win_rect.w, win_rect.h,0,&window,&renderer);
        Event::create();
        Keyboard::create();
        Frame::create();
        event = Event::instance();
        keyboard = Keyboard::instance();
        frame = Frame::instance();
      }catch(char *error){
        fprintf(stderr,"%s\n",error);
        Event::destroy();
        Keyboard::destroy();
        Frame::destroy();
        abort();
      }
  }

  static void update(void){
    dnscript->update();
  }

  static void draw(void){
    dnscript->draw();
  }

  static void quit(void){
    Event::destroy();
    Keyboard::destroy();
    Frame::destroy();
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
  }

  static bool polling_event(void){
    SDL_Event ev;
    SDL_Keycode key;
    while ( SDL_PollEvent(&ev) ){
      event->set_event(ev);
      switch(ev.type){
        case SDL_QUIT:
          return false;
          break;
        case SDL_KEYDOWN:
        {
          key = ev.key.keysym.sym;
          keyboard->keyon(key);
          if(key == SDLK_ESCAPE){ return false; }
        }
          break;
        case SDL_KEYUP:
        {
          key = ev.key.keysym.sym;
          keyboard->keyoff(key);
          break;
        }
      }
    }
    return true;
  }
  static int main(int argc,char *argv[]){
    while (polling_event()) {
      update();
      draw();
      frame->count_up();
      SDL_Delay((Uint32)timer_wait_mil);
    }
    quit();
    return 0;
  }
};

#endif
