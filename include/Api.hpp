#ifndef __API_HPP__
#define __API_HPP__

#include <string>
/* ### Singleton class ### */
class Object;
class Api{
private:
  Api(){;}
  ~Api(){;}
  Api(const Api&){;}
  static Api* mInstance;
public:
  static Api* instance();
  static void create();
  static void destroy();
  void LoadGraphic(Object* target,std::string filename);
  void SetTexture(Object* target,std::string filename);
  void SetGraphicRect(Object* target,GLfloat sx,GLfloat sy,GLfloat dx,GLfloat dy);
  void DrawGraphic(Object* target,GLfloat x,GLfloat y);
};

#endif
