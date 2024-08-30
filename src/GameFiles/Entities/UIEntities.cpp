#include "UIEntities.h"
#include <vector>

int HPSPRITE[5][26]= {
	{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
	{ 0,1,0,1,0,1,1,1,0,1,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0 },
	{ 0,1,1,1,0,1,1,1,0,0,0,1,2,2,2,2,2,2,2,2,2,2,2,2,1,0 },
	{ 0,1,0,1,0,1,0,0,0,1,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0 },
	{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 }
};

UISpriteGroup::UISpriteGroup() : waveSprite(7, 25, (int*)WAVESPRITE), waveSprite_S(7, 25, (int*)WAVESPRITE_S), hpSprite(5, 26, nullptr), pausedSprite(28, 41, (int*)PAUSEDMENU), backSprite(7, 25, (int*)BACK), backSprite_S(7, 25, (int*)BACK_S),
                                 exitSprite(7, 25, (int*)EXIT), exitSprite_S(7, 25, (int*)EXIT_S), gameOver(7, 51, (int*)GAMEOVER), gameOver_S(7, 51, (int*)GAMEOVER_S), scoreSprite(7, 33, (int*)SCORE), scoreSprite_S(7, 33, (int*)SCORE_S) {
  hpSprite.data = (int*)HPSPRITE;
}

WaveUIEntity::WaveUIEntity(UISpriteGroup* sprGrp) : spriteGroup(sprGrp) {
  defineNumbers_();
  justification_ = 0;
  numberSprite_.cols = 6;
  numberSprite_.rows = 7;

}

WaveUIEntity::~WaveUIEntity() {

}

void WaveUIEntity::update() {
  if (move) {
    if (getPosition().x < desiredPosition_.x - animationSpeed_ || getPosition().x > desiredPosition_.x + animationSpeed_) {
      shiftEntity(Coord3D (-animationSpeed_, 0, 0));
    }
    if (getPosition().z < desiredPosition_.z - animationSpeed_ || getPosition().z > desiredPosition_.z + animationSpeed_) {
      shiftEntity(Coord3D (0, 0, animationSpeed_));
    }
  }
}

void WaveUIEntity::setWave(int wve) {
  move = false;
  currentWave_ = wve;
  if (currentWave_ == 0) {
    numberSprite_.data = (int*)numberSprites_[0].data();
    if (!score_) combineSprites_(&spriteGroup->waveSprite, &numberSprite_);
    else combineSprites_(&spriteGroup->scoreSprite, &numberSprite_);
  }
  else {
    if (score_) sprites_[0] = &spriteGroup->scoreSprite;
    else sprites_[0] = &spriteGroup->waveSprite;

    int digs = floor(log10(currentWave_)) + 1;
    std::vector<int> digits(digs, 0);
    int sum = 0;
    for (int i = digs-1; i > -1; i--) { // Computationally expensive but functionally complete, only called every wave so not too often.
      digits[i] = currentWave_ % int(pow(10, digs-i)) - sum;
      sum += digits[i];
      digits[i] = digits[i] / pow(10, digs-i-1);
    }

    for (int i = 0; i < digs; i++) {
      numberSprite_.data = (int*)numberSprites_[2*digits[i]].data();
      combineSprites_(sprites_[0], &numberSprite_);
    }
  }
  moveEntityByPixel(42-floor(getCols(0)/2), 24);
}

void WaveUIEntity::combineSprites_(Sprite* spr1, Sprite* spr2) {
  int x1 = spr1->cols;
  int y1 = spr1->rows;
  int x2 = spr2->cols;
  int y2 = spr2->rows;

  std::vector<int> newSprite((x1+x2)*y1, 0);
  for (int i = 0; i < y1; i++) {
    for (int j = 0; j < x1; j++) {
      newSprite[i * (x1+x2) + j] = spr1->data[i * x1 + j];
    }
    for (int k = 0; k < x2; k++) {
      newSprite[i * (x1+x2) + x1 + k] = spr2->data[i*x2 + k];
    }
  }
  sprite_ = newSprite;

  currentSprite_.rows = y1;
  currentSprite_.cols = x1+x2;
  currentSprite_.data = (int*)sprite_.data();

  sprites_[0] = &currentSprite_;
}

void WaveUIEntity::defineNumbers_() {
  numberSprites_.resize(20, std::vector<int>(42));
  // I don't like this.
  numberSprites_[0] = {2,2,2,2,2,2,2,2,1,1,1,2,2,1,2,2,2,1,2,1,2,2,2,1,2,1,2,2,2,1,2,2,1,1,1,2,2,2,2,2,2,2};
  numberSprites_[1] = {2,2,1,1,1,2,2,1,2,2,2,1,1,2,1,1,1,2,1,2,1,2,1,2,1,2,1,1,1,2,2,1,2,2,2,1,2,2,1,1,1,2};
  numberSprites_[2] = {2,2,2,2,2,2,2,2,1,1,2,2,2,2,2,1,2,2,2,2,2,1,2,2,2,2,2,1,2,2,2,2,1,1,1,2,2,2,2,2,2,2};
  numberSprites_[3] = {2,2,1,1,2,2,2,1,2,2,1,2,2,2,1,2,1,2,2,2,1,2,1,2,2,2,1,2,1,2,2,1,2,2,2,1,2,2,1,1,1,2};
  numberSprites_[4] = {2,2,2,2,2,2,2,2,1,1,1,2,2,1,2,2,2,1,2,2,2,1,1,2,2,2,1,2,2,2,2,1,1,1,1,1,2,2,2,2,2,2};
  numberSprites_[5] = {2,2,1,1,1,2,2,1,2,2,2,1,1,2,1,1,1,2,2,1,1,2,2,1,2,1,2,1,1,1,1,2,2,2,2,2,2,1,1,1,1,1};
  numberSprites_[6] = {2,2,2,2,2,2,2,1,1,1,1,2,2,2,2,2,2,1,2,2,1,1,1,2,2,2,2,2,2,1,2,1,1,1,1,2,2,2,2,2,2,2};
  numberSprites_[7] = {2,1,1,1,1,2,1,2,2,2,2,1,2,1,1,1,1,2,2,1,2,2,2,1,2,1,1,1,1,2,1,2,2,2,2,1,2,1,1,1,1,2};
  numberSprites_[8] = {2,2,2,2,2,2,2,2,2,1,1,2,2,2,1,2,1,2,2,1,2,2,1,2,2,1,1,1,1,1,2,2,2,2,1,2,2,2,2,2,2,2};
  numberSprites_[9] = {2,2,2,1,1,2,2,2,1,2,2,1,2,1,2,1,2,1,1,2,1,1,2,1,1,2,2,2,2,2,2,1,1,1,2,1,2,2,2,2,1,2};
  numberSprites_[10] = {2,2,2,2,2,2,2,1,1,1,1,1,2,1,2,2,2,2,2,1,1,1,1,2,2,2,2,2,2,1,2,1,1,1,1,2,2,2,2,2,2,2};
  numberSprites_[11] = {2,1,1,1,1,1,1,2,2,2,2,2,1,2,1,1,1,1,1,2,2,2,2,1,2,1,1,1,1,2,1,2,2,2,2,1,2,1,1,1,1,2};
  numberSprites_[12] = {2,2,2,2,2,2,2,2,1,1,1,2,2,1,2,2,2,2,2,1,1,1,1,2,2,1,2,2,2,1,2,2,1,1,1,2,2,2,2,2,2,2};
  numberSprites_[13] = {2,2,1,1,1,2,2,1,2,2,2,1,1,2,1,1,1,2,1,2,2,2,2,1,1,2,1,1,1,2,2,1,2,2,2,1,2,2,1,1,1,2};
  numberSprites_[14] = {2,2,2,2,2,2,2,1,1,1,1,2,2,2,2,2,2,1,2,2,2,2,1,2,2,2,2,1,2,2,2,2,2,1,2,2,2,2,2,2,2,2};
  numberSprites_[15] = {2,1,1,1,1,2,1,2,2,2,2,1,2,1,1,1,1,2,2,2,2,1,2,1,2,2,1,2,1,2,2,2,1,2,1,2,2,2,2,1,2,2};
  numberSprites_[16] = {2,2,2,2,2,2,2,2,1,1,1,2,2,1,2,2,2,1,2,2,1,1,1,2,2,1,2,2,2,1,2,2,1,1,1,2,2,2,2,2,2,2};
  numberSprites_[17] = {2,2,1,1,1,2,2,1,2,2,2,1,1,2,1,1,1,2,2,1,2,2,2,1,1,2,1,1,1,2,2,1,2,2,2,1,2,2,1,1,1,2};
  numberSprites_[18] = {2,2,2,2,2,2,2,2,1,1,1,2,2,1,2,2,2,1,2,2,1,1,1,1,2,2,2,2,2,1,2,2,1,1,1,2,2,2,2,2,2,2};
  numberSprites_[19] = {2,2,1,1,1,2,2,1,2,2,2,1,1,2,1,1,1,2,2,1,2,2,2,2,2,2,1,1,1,2,2,1,2,2,2,1,2,2,1,1,1,2};
}

HPUIEntity::HPUIEntity(UISpriteGroup* sprGrp) : spriteGroup_(sprGrp) {
  setSprite(&spriteGroup_->hpSprite);
  //moveEntity(Coord3D (0, 0.02, 0));
  moveEntity(Coord3D (0.05,0.02,0.8));
  //moveEntityByPixel(4, 16);
  justification_ = 0;
}

void HPUIEntity::update() {
  if (updateSprite_) {
    updateSprite_ = false;
    int cells = ceil(12*currentHealth_/maxHealth_);
    for (int i = 64; i < 76 ; i++) {
      if (i < 64 + cells) {
        spriteGroup_->hpSprite.data[i] = 1;
      }
      else {
        spriteGroup_->hpSprite.data[i] = 2;
      }
    }
  }
}

bool HPUIEntity::removeHealth(int damage) {
  // Removes health, returns true if health is now 0.
  currentHealth_ -= damage;
  updateSprite_ = true;
  if (currentHealth_ < 0) {
    currentHealth_ = 0;
    return true;
  }
  else return false;
  printf("Current Health: %i\n", currentHealth_);
}

bool HPUIEntity::heal(int health) {
  // Heals the user, returns true if healed to max health.
  currentHealth_ += health;
  updateSprite_ = true;
  if (currentHealth_ > maxHealth_) {
    currentHealth_ = maxHealth_;
    return true;
  }
  else return false;
}

int HPUIEntity::getHealth() {
  return currentHealth_;
}

PauseMenuEntity::PauseMenuEntity(UISpriteGroup* sprGrp) : spriteGroup_(sprGrp) {
  setSprite(&spriteGroup_->pausedSprite);
  moveEntity(Coord3D (0.5, -1, 0.5));
}

void PauseMenuEntity::update() {
  if (paused_) {
    if (getPosition().y != 0.005) moveEntity(Coord3D (0.5, 0.005, 0.3));
  }
  else {
    if (getPosition().y != -1) moveEntity(Coord3D (0.5, -1, 0.3));
  }
}

BackButtonEntity::BackButtonEntity(UISpriteGroup* uiSprites, MenuSpriteGroup* menuSprites, Messenger* mssngr) : MenuEntityBase(menuSprites, mssngr), uiSprites_(uiSprites){
  moveEntity(Coord3D (0.5,-1,0.5));
  spr = &uiSprites_->backSprite;
  spr_s = &uiSprites_->backSprite_S;
  setSprite(spr);
}

void BackButtonEntity::shot() {
  messenger_->Notify(EventMSG::EVENT_PAUSE_GAME);
}

void BackButtonEntity::customUpdate() {
  if (paused_) {
    if (getPosition().y != 0.004) moveEntity(Coord3D (0.5, 0.004, 0.5));
  }
  else {
    if (getPosition().y != -1) moveEntity(Coord3D (0.5, -1, 0.5));
  }
}

ExitButtonEntity::ExitButtonEntity(UISpriteGroup* uiSprites, MenuSpriteGroup* menuSprites, Messenger* mssngr) : MenuEntityBase(menuSprites, mssngr), uiSprites_(uiSprites){
  moveEntity(Coord3D (0.5,-1,0.33));
  spr = &uiSprites_->exitSprite;
  spr_s = &uiSprites_->exitSprite_S;
  setSprite(spr);
}

void ExitButtonEntity::shot() {
  messenger_->Notify(EventMSG::EVENT_QUIT);
}

void ExitButtonEntity::customUpdate() {
  if (paused_) {
    if (getPosition().y != targetPos.y) moveEntity(targetPos);
  }
  else {
    if (getPosition().y != -1) moveEntity(Coord3D (0.5, -1, 0.33));
  }
}

GameOverEntity::GameOverEntity(UISpriteGroup* uiSprites) : uiSprites_(uiSprites) {
  moveEntity(Coord3D (0.1, 0.1, 0.7));
  setSprite(&uiSprites_->gameOver);
  justification_ = 0;
}

ScoreEntity::ScoreEntity(UISpriteGroup* sprites, int score) : WaveUIEntity(sprites), scoreVal_(score) {
  score_ = true;
  setWave(scoreVal_);
  moveEntity(Coord3D (0.1, 0.1, 0.5));
}

void ScoreEntity::update() {}