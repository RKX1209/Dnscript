class Api;
class Player;
class player_test{
private:
  Api* api;
  Player* player;
  bool bNextShot;
  int shotCount;
public:
  player_test(Player*);
  ~player_test();
  void Initialize();
  void MainLoop();
  void DrawLoop();
  void SpellCard();
};
