#include "Zombie.h"

Zombie::Zombie(ZombieSpriteGroup* sprgrp, bool reverse, Messenger* messenger, Timer* timer, bool decorative, bool createdByScene) : sprgrp(sprgrp), decorative_(decorative), Entity(messenger, createdByScene), timer_(timer) {
  if (!reverse) {
    setSprite(&sprgrp->zombie0Sprite, 0);
    setSprite(&sprgrp->zombie1Sprite, 1);
    setSprite(&sprgrp->zombie2Sprite, 2);
    setSprite(&sprgrp->zombie3Sprite, 3);
    setSprite(&sprgrp->zombie4Sprite, 4);
    setSprite(&sprgrp->zombie5Sprite, 5);
  }
  else {
    setSprite(&sprgrp->zombie0SpriteR, 0);
    setSprite(&sprgrp->zombie1SpriteR, 1);
    setSprite(&sprgrp->zombie2SpriteR, 2);
    setSprite(&sprgrp->zombie3SpriteR, 3);
    setSprite(&sprgrp->zombie4SpriteR, 4);
    setSprite(&sprgrp->zombie5SpriteR, 5);
  }
}

Zombie::~Zombie() {
  if (messenger_ != nullptr) {
    messenger_->Notify(EventMSG::EVENT_ZOMBIE_KILLED);
  }
}

void Zombie::shot() {
  if (!paused_) {
    Alive = false;
  }
}

void Zombie::update() {
  if (!decorative_ && !paused_ && getPosition().y - speed_ > 0.01) {
    shiftEntity(Coord3D (0,-speed_,0));
  }
  else if (!decorative_ && !paused_ && timer_ != nullptr && timer_->elapsed_time().count() / 1000 > previousHitTimems_ + hitDelayms_ ) {
    // Add hit logic here:
    // Can't use a timer, can't really just use flags, could add a second messenger just for Game Scenes and Zombies. Going to use a timer anyway
    printf("Hit Player\n");
    previousHitTimems_ = timer_->elapsed_time().count() / 1000;
    messenger_->Notify(EventMSG::EVENT_PLAYER_HIT);
  }
}

void Zombie::setSpeed(double spd) {
  speed_ = spd;
}

ZombieSpriteGroup::ZombieSpriteGroup() {
  zombie0Sprite.cols = 27;
  zombie0Sprite.rows = 42;
  zombie0Sprite.data = (int*)SPRITEZOMBIE0;

  zombie1Sprite.cols = 23;
  zombie1Sprite.rows = 35;
  zombie1Sprite.data = (int*)SPRITEZOMBIE1;

  zombie2Sprite.cols = 18;
  zombie2Sprite.rows = 28;
  zombie2Sprite.data = (int*)SPRITEZOMBIE2;

  zombie3Sprite.cols = 14;
  zombie3Sprite.rows = 21;
  zombie3Sprite.data = (int*)SPRITEZOMBIE3;

  zombie4Sprite.cols = 9;
  zombie4Sprite.rows = 14;
  zombie4Sprite.data = (int*)SPRITEZOMBIE4;

  zombie5Sprite.cols = 9;
  zombie5Sprite.rows = 14;
  zombie5Sprite.data = (int*)SPRITEZOMBIE4;

  zombie0SpriteR = zombie0Sprite;
  zombie0SpriteR.reverse = true;
  
  zombie1SpriteR = zombie1Sprite;
  zombie1SpriteR.reverse = true;

  zombie2SpriteR = zombie2Sprite;
  zombie2SpriteR.reverse = true;

  zombie3SpriteR = zombie3Sprite;
  zombie3SpriteR.reverse = true;
  
  zombie4SpriteR = zombie4Sprite;
  zombie4SpriteR.reverse = true;

  zombie5SpriteR = zombie5Sprite;
  zombie5SpriteR.reverse = true;
}