#ifndef MENUSCENE_H
#define MENUSCENE_H

#include "Scene.h"
#include "MenuEntities.h"
#include "Player.h"
#include "Zombie.h"
#include "Background.h"
#include "Configs.h"
#include "UIEntities.h"

class MainMenuScene : public Scene {
  public:
  MainMenuScene(Player* player, Messenger* mssngr, InputConfig* config);
  ~MainMenuScene();


  private:
  Title* title_;
  StartEntity* start_;
  OptionsEntity* options_;
  Zombie* decZombie_;
  Background* background_;

  ZombieSpriteGroup* zombieSprites_;
  MenuSpriteGroup* menuSprites_;

  Messenger* mssngr_;
};

class OptionsMenuScene : public Scene {
  public:
  OptionsMenuScene(Entity* player, Messenger* messenger, InputConfig* config);
  ~OptionsMenuScene();

  private:
  Background* background_;
  FpsOptionEntity* fps_;
  DBGOptionEntity* dbg_;
  RemapOptionEntity* remap_;
  MenuSpriteGroup* menuSprites_;

};


#endif