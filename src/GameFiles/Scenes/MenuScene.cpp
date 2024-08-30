#include "MenuScene.h"

MainMenuScene::MainMenuScene(Player* player, Messenger* mssngr, InputConfig* config) : Scene(Coord3D (0,0,0), Coord3D (1,1,1), player, config), mssngr_(mssngr){

  menuSprites_ = new MenuSpriteGroup;

  title_ = new Title(menuSprites_);
  addEntity(title_);

  start_ = new StartEntity(menuSprites_);
  addEntity(start_);

  options_ = new OptionsEntity(menuSprites_);
  addEntity(options_);

  zombieSprites_ = new ZombieSpriteGroup;

  decZombie_ = new Zombie(zombieSprites_, false, nullptr, nullptr, true, false);
  decZombie_->moveEntity(Coord3D (0.7,0.01,0));
  addEntity(decZombie_);

  background_ = new Background;
  addEntity(background_);

}

MainMenuScene::~MainMenuScene() {
  delete title_;
  title_ = nullptr;
  delete start_;
  start_ = nullptr;
  delete options_;
  options_ = nullptr;
  delete background_;
  background_ = nullptr;
  delete menuSprites_;

}


OptionsMenuScene::OptionsMenuScene(Entity* player, Messenger* messenger, InputConfig* config) : Scene(Coord3D (0,0,0), Coord3D (1,1,1), player, config) {
  menuSprites_ = new MenuSpriteGroup;

  background_ = new Background;
  addEntity(background_);

  fps_ = new FpsOptionEntity(menuSprites_, messenger);
  addEntity(fps_);

  dbg_ = new DBGOptionEntity(menuSprites_, messenger);
  addEntity(dbg_);

  remap_ = new RemapOptionEntity(menuSprites_, messenger);
  addEntity(remap_);

}

OptionsMenuScene::~OptionsMenuScene() {
  delete menuSprites_;
  delete background_;
  background_ = nullptr;
  delete fps_;
  delete dbg_;
  delete remap_;
}