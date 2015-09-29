#include <GL/glut.h>
#include <GL/freeglut.h>

#include "Dnscript.hpp"
#include "Window.hpp"

const int Window::win_posx = 100;
const int Window::win_posy = 100;
const int Window::win_width = 200;
const int Window::win_height = 200;
const char* Window::win_title = "Dnscript ver1.0";
const double Window::fps = 30;
const int Window::timer_wait_mil = 1.0 / Window::fps * 1000;
Dnscript* Window::dnscript = new Dnscript();

/* entry point */
int main(int argc,char *argv[]){
  Window::main(argc,argv);
  delete Window::dnscript;
}
