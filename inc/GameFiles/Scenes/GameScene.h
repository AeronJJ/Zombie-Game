#ifndef GAMESCENE_H
#define GAMESCENE_H

#include "Scene.h"
#include "Player.h"
#include "Zombie.h"
#include "Background.h"
#include "Commands.h"
#include "UIEntities.h"
#include "Configs.h"

//#include <time.h>
//#include <stdlib.h>

class GameScene : public Scene {
  public:
  GameScene(Player* player, Timer* time, WaveUIEntity* waves, Messenger* messenger, HPUIEntity* hp, PauseMenuEntity* pauseEnt, InputConfig* config, BackButtonEntity* backButt, ExitButtonEntity* exitButt);
  ~GameScene();

  Scene* update() override;
  void nextWave();

  void setLeftWindow(Scene*);
  void setRightWindow(Scene*);

  int getRemaining();
  int getAlive();

  int getWave();

  void togglePause();

  private:
  Messenger* messenger_;
  bool messageSent_ = false;
  void spawnLogic_();
  int spawnDelay_ = 50;
  int calculateAlive_(); // Calculates how many zombies should be on screen based on the wave.
  int wave_ = 0;
  int alive_ = 0;
  int remaining_ = 0;
  bool paused_ = false;
  Timer* time_;
  int waveStartTimems_ = 0;
  int waveDelayms_ = 2000; // Delay in milliseconds between a wave ending, and zombies starting to spawn in the next wave.

  int baseSpeed_ = 5; // This value is added to the current wave, then +- 10%, then divided by 10,000.

  int freeEntities = 0;
  
  Background* background_;

  Zombie* newZombie_;

  ZombieSpriteGroup* zombieSprites_;

  WaveUIEntity* wavesEntity_;
  HPUIEntity* hpEntity_;
  PauseMenuEntity* pauseEntity_;
  BackButtonEntity* backButton_;
  ExitButtonEntity* exitButton_;

};

#endif