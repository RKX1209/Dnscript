class Api;
class Enemy;
class enemy_test{
private:
  Api* api;
  Enemy* enemy;
  int count;
  int cx;
  int imgAngle;
  int shotAngle;
public:
  enemy_test(Enemy*);
  ~enemy_test();
  void Initialize();
  void MainLoop();
  void DrawLoop();

};
