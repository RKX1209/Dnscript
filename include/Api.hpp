#ifndef __API_HPP__
#define __API_HPP__

/* ### Singleton class ### */
class Character;
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
  void LoadGraphic(Character* target,char* filename);
  void SetTexture(Character* target,char* filename);
  void SetGraphicRect(Character* target,int sx,int sy,int dx,int dy);
};

#endif
