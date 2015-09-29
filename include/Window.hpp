#ifndef __WINDOW_HPP__
#define __WINDOW_HPP__

class Dnscript;
class Window{
private:
  static const int win_posx;
  static const int win_posy;
  static const int win_width;
  static const int win_height;
  static const char* win_title;
  static const double fps;
  static const int timer_wait_mil;
public:
  static Dnscript* dnscript;
  Window(void) { ; }
  static void init(void){
    glClearColor(0.5, 0.5, 1.0, 1.0);

  	glEnable(GL_DEPTH_TEST);
  	glEnable(GL_LIGHTING);
  	glEnable(GL_LIGHT0);

  	glEnable(GL_CULL_FACE);
  	glCullFace(GL_BACK);
  }

  static void draw(void){
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    dnscript->draw();
  }

  static void repaint(void){
    draw();
    glutSwapBuffers();
  }

  static void main_loop(int value){
    glutTimerFunc(timer_wait_mil, main_loop, 0);
  	glutSwapBuffers();
    dnscript->update();
    draw();
  }

  static void key_push(unsigned char key, int x, int y){

  }

  static void key_release(unsigned char key, int x, int y){
  }

  static void close(void){
    /* cleanup objects */

  }

  static int main(int argc,char *argv[]){
    glutInit(&argc,argv);
    glutInitWindowPosition(win_posx,win_posy);
    glutInitWindowSize(win_height,win_width);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
    glutCreateWindow(win_title);
    glutDisplayFunc(repaint);	//[handler] window repaint
    glutCloseFunc(close);	//[handler] window close
    glutKeyboardFunc(key_push);	//[handler] keyboard push
    glutKeyboardUpFunc(key_release);	//[handler] keyboard release
    glutTimerFunc(timer_wait_mil, main_loop, 0);	//[handler] interval timer

    init();

    glutMainLoop();
    return 0;
  }
};

#endif
