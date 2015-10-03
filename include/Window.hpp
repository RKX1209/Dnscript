#ifndef __WINDOW_HPP__
#define __WINDOW_HPP__

#include <SDL.h>

class Dnscript;

class Window{
public:
  static SDL_Window* window;
  static SDL_Renderer* renderer;
  static SDL_Rect win_rect;
  static const char* win_title;
  static const double fps;
  static const int timer_wait_mil;
  static Dnscript* dnscript;

  Window(void) { ; }

  static void init(void){
    try{
        if( SDL_Init(SDL_INIT_EVERYTHING) < 0 ) throw "[*ERROR*] Window::main SDL_Init fail";
        SDL_CreateWindowAndRenderer(win_rect.w, win_rect.h,0,&window,&renderer);
      }catch(char *error){
        fprintf(stderr,"%s\n",error);
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
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
  }

  static bool polling_event(void){
    SDL_Event ev;
    SDL_Keycode key;
    while ( SDL_PollEvent(&ev) ){
      switch(ev.type){
        case SDL_QUIT:
          return false;
          break;
        case SDL_KEYDOWN:
        {
          key = ev.key.keysym.sym;
          if(key == SDLK_ESCAPE){ return false; }
        }
          break;
      }
    }
    return true;
  }

  static int main(int argc,char *argv[]){
    while (polling_event()) {
      update();
      draw();
      SDL_Delay((Uint32)timer_wait_mil);
    }
    quit();
    return 0;
  }
};

#endif
