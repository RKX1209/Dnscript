class Title;
class Select;
class Game;
class Dnscript{
private:
  Title* title;
  Select* select;
  Game* game;
public:
  enum SeqID{
    SEQ_TITLE,
    SEQ_STAGE_SELECT,
    SEQ_GAME,
    SEQ_NONE,
  };
  Dnscript(void);
  ~Dnscript(void);
  void update(void);
  void draw(void);

};
