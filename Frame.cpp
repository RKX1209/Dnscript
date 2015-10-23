#include <cstdio>
#include <cstdlib>
#include "Frame.hpp"

Frame* Frame::mInstance = 0;

Frame* Frame::instance(){
    return mInstance;
}

void Frame::create(){
  try{
    if(mInstance) throw "[*ERROR*] Frame::create() cannnot create instance twice";
    mInstance = new Frame();
  }catch(const char *error){
    fprintf(stderr,"%s\n",error);
    abort();
  }
}

void Frame::destroy(){
  delete mInstance;
  mInstance = 0;
}

Frame::Frame(){
  frame = 0;
}

void Frame::count_up(){
  frame = (frame + 1) % FRAME_MAX;
}

int Frame::get_frame(){
  return frame;
}

int Frame::get_next_frame(int plus){
    return (frame + plus) % FRAME_MAX;
}
