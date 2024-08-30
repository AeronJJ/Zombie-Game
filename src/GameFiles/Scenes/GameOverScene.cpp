#include "GameOverScene.h"

GameOverScene::GameOverScene(Player* player, Messenger* mssngr, InputConfig* config, UISpriteGroup* uiSprites, MenuSpriteGroup* menuSprites, int score) : 
                            Scene(Coord3D (0,0,0), Coord3D (1,1,1), player, config), uiSprites_(uiSprites), menuSprites_(menuSprites), mssngr_(mssngr), scoreVal_(score) 
{
  exit_ = new ExitButtonEntity(uiSprites_, menuSprites_, mssngr_);
  gameOver_ = new GameOverEntity(uiSprites_);
  score_ = new ScoreEntity(uiSprites_, scoreVal_);
  background_ = new Background();
  
  addEntity(exit_);
  addEntity(gameOver_);
  addEntity(score_);
  addEntity(background_);

  exit_->togglePause();
  exit_->targetPos = Coord3D (0.1, 0.1, 0.25);
  exit_->setJustification(0);

}

GameOverScene::~GameOverScene() {
  delete exit_;
  delete gameOver_;
  delete score_;
  delete background_;
}