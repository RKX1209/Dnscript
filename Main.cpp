#include <cstdio>

#include "Event.hpp"
#include "Window.hpp"

SDL_Window* Window::window;
SDL_Renderer* Window::renderer;
SDL_Rect Window::win_rect;
const double Window::fps = 30;
const int Window::timer_wait_mil = 1.0 / Window::fps * 1000;
Dnscript* Window::dnscript;
const char* Window::win_title = "Dnscript ver 1.0";
Event* Window::event;
Keyboard* Window::keyboard;

/* entry point */
int main(int argc,char *argv[]){
  Window::win_rect.x = 100;
  Window::win_rect.y = 100;
  Window::win_rect.w = 700;
  Window::win_rect.h = 600;
  Window::init();
  Window::dnscript = new Dnscript();
  Window::main(argc,argv);
  delete Window::dnscript;
}
