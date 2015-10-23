#ifndef __FRAME_HPP__
#define __FRAME_HPP__

/* ### Singleton class ### */
class Frame{
private:
  int frame;
  Frame();
  ~Frame(){;}
  Frame(const Frame&){;}
  static Frame* mInstance;
public:
  void count_up();
  int get_frame();
  int get_next_frame(int);
  static const int FRAME_MAX = 0x1000000;
  static Frame* instance();
  static void create();
  static void destroy();
};
#endif
