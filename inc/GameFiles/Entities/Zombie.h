#ifndef ZOMBIE_H
#define ZOMBIE_H

#include "Entity.h"
#include "Action.h"

class ZombieSpriteGroup {
  public:
    ZombieSpriteGroup();
    Sprite zombie0Sprite;
    Sprite zombie1Sprite;
    Sprite zombie2Sprite;
    Sprite zombie3Sprite;
    Sprite zombie4Sprite;
    Sprite zombie5Sprite;

    Sprite zombie0SpriteR;
    Sprite zombie1SpriteR;
    Sprite zombie2SpriteR;
    Sprite zombie3SpriteR;
    Sprite zombie4SpriteR;
    Sprite zombie5SpriteR;
  private:
};

class Zombie : public Entity {
  public:
    Zombie(ZombieSpriteGroup* sprgrp, bool reverse, Messenger* messenger, Timer* timer, bool decorative_ = false, bool createdByScene = true);
    ~Zombie();
    void shot() override;
    void update() override;
    void setSpeed(double spd);
  private:
    bool decorative_;
    double speed_ = 0.0005;
    ZombieSpriteGroup* sprgrp;
    Timer* timer_;
    int previousHitTimems_ = 0;
    int hitDelayms_ = 1000;
};

const int SPRITEZOMBIE0[42][27] = {
    { 0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
    { 0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
    { 0,1,0,0,0,0,1,1,1,1,1,1,1,1,0,0,1,1,0,0,0,0,0,0,0,0,0 },
    { 0,1,0,0,1,1,2,2,2,2,2,2,2,2,1,1,0,0,0,0,0,0,0,0,0,0,0 },
    { 0,0,1,1,2,2,2,2,2,2,2,2,2,2,2,2,1,1,0,0,0,0,0,0,0,0,0 },
    { 0,0,1,2,2,2,2,2,2,2,2,2,2,2,2,2,1,0,0,0,0,0,0,0,0,0,0 },
    { 0,0,1,2,2,2,2,2,2,2,1,1,1,2,2,2,2,1,1,1,0,0,0,0,0,0,0 },
    { 0,1,2,2,2,2,2,2,2,1,2,2,2,1,2,2,2,1,0,0,1,0,0,0,0,0,0 },
    { 0,1,2,2,2,2,2,2,1,2,2,2,2,2,1,2,2,1,0,0,0,0,0,0,0,0,0 },
    { 0,1,1,1,2,2,2,2,1,2,2,1,2,2,1,2,2,2,1,0,0,0,0,0,0,0,0 },
    { 1,2,2,2,1,2,2,2,1,2,2,2,2,2,1,2,2,2,1,1,0,0,0,0,0,0,0 },
    { 1,2,1,2,1,2,2,2,2,1,2,2,2,1,2,2,2,2,1,0,1,0,0,0,0,0,0 },
    { 1,2,2,2,1,2,1,1,2,2,1,1,1,2,2,2,2,1,0,0,0,0,0,0,0,0,0 },
    { 0,1,1,1,2,2,2,2,2,2,2,2,2,2,2,2,2,1,0,0,0,0,0,0,0,0,0 },
    { 0,0,1,2,2,2,1,1,2,1,2,2,2,2,2,2,1,0,0,0,0,0,0,0,0,0,0 },
    { 0,0,1,1,1,1,2,2,1,2,1,1,2,2,2,1,1,0,0,0,0,0,0,0,0,0,0 },
    { 0,0,0,0,1,2,2,2,2,2,2,2,2,2,1,2,2,1,0,0,0,0,0,0,0,0,0 },
    { 0,0,0,0,0,1,2,2,2,2,1,2,2,1,2,2,2,2,1,0,0,0,0,0,0,0,0 },
    { 0,0,0,0,1,2,1,2,1,1,2,2,2,1,2,1,2,2,2,1,0,0,0,0,0,0,0 },
    { 0,0,0,0,1,2,2,2,2,2,2,2,1,2,2,1,2,2,2,2,1,0,0,0,0,0,0 },
    { 0,0,0,0,0,1,1,1,1,1,1,1,2,2,2,1,2,2,2,2,1,0,0,0,0,0,0 },
    { 0,0,0,0,0,0,0,1,1,2,1,2,1,2,2,1,2,2,1,2,2,1,0,0,0,0,0 },
    { 0,0,0,0,0,0,0,0,0,1,2,2,1,2,2,1,2,2,1,2,2,1,0,0,0,0,0 },
    { 0,0,0,0,0,0,0,0,0,1,2,2,2,1,1,2,2,2,1,2,2,2,1,0,0,0,0 },
    { 0,0,0,0,0,0,0,0,0,1,2,2,2,2,1,2,2,2,1,2,2,2,2,1,0,0,0 },
    { 0,0,0,0,0,0,0,0,0,1,2,2,2,2,1,2,2,2,1,2,2,2,2,1,0,0,0 },
    { 0,0,0,0,0,0,0,0,0,1,2,2,2,1,2,2,2,1,2,2,2,1,1,1,0,0,0 },
    { 0,0,0,0,0,0,0,0,1,2,2,2,2,1,2,2,2,1,1,2,1,2,2,1,0,0,0 },
    { 0,0,0,0,0,0,0,0,1,2,2,2,2,1,1,1,2,2,1,1,2,2,2,1,0,0,0 },
    { 0,0,0,0,0,0,0,0,0,1,1,1,2,1,2,2,1,1,1,2,2,2,2,1,0,0,0 },
    { 0,0,0,0,0,0,0,0,1,2,2,2,1,2,2,2,2,1,2,2,2,2,2,1,0,0,0 },
    { 0,0,0,0,0,0,0,0,1,2,2,2,1,2,2,2,2,1,1,2,2,2,2,1,0,0,0 },
    { 0,0,0,0,0,0,0,0,1,2,2,2,1,2,2,2,2,2,1,2,2,2,1,0,0,0,0 },
    { 0,0,0,0,0,0,0,0,0,1,2,2,2,1,2,1,2,2,1,2,2,2,2,1,0,0,0 },
    { 0,0,0,0,0,0,0,0,0,0,1,1,1,2,1,2,1,1,2,2,2,2,2,2,1,1,1 },
    { 0,0,0,0,0,0,0,0,0,0,0,0,1,2,2,2,2,1,2,2,2,2,2,2,2,1,0 },
    { 0,0,0,0,0,0,0,0,0,0,0,1,2,2,2,2,2,1,1,1,2,2,2,2,2,1,0 },
    { 0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,2,1,2,2,2,1,1,2,2,2,2,1 },
    { 0,0,0,0,0,0,0,0,0,0,0,1,2,2,2,1,2,2,2,2,2,2,1,2,2,2,1 },
    { 0,0,0,0,0,0,0,0,0,0,0,1,2,2,2,1,2,2,2,2,2,2,2,1,1,1,0 },
    { 0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,2,2,2,2,1,1,0,0,0,0 },
    { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,0,0,0,0,0,0 }
    };


const int SPRITEZOMBIE1[35][23] = {
	{ 0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
	{ 0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
	{ 0,1,0,0,0,1,1,1,1,1,1,1,0,0,1,0,0,0,0,0,0,0,0 },
	{ 0,1,0,1,1,2,2,2,2,2,2,2,1,1,0,0,0,0,0,0,0,0,0 },
	{ 0,0,1,2,2,2,2,2,2,2,2,2,2,1,0,0,0,0,0,0,0,0,0 },
	{ 0,0,1,2,2,2,2,2,2,1,1,2,2,2,1,1,1,0,0,0,0,0,0 },
	{ 0,1,2,2,2,2,2,2,1,2,2,1,2,2,1,0,0,1,0,0,0,0,0 },
	{ 0,1,1,1,2,2,2,1,2,2,2,2,1,2,1,0,0,0,0,0,0,0,0 },
	{ 1,2,2,2,1,2,2,1,2,1,2,2,1,2,2,1,1,0,0,0,0,0,0 },
	{ 1,2,1,2,1,2,2,2,1,2,2,1,2,2,2,1,0,1,0,0,0,0,0 },
	{ 1,2,2,2,1,2,2,2,2,1,1,2,2,2,1,0,0,0,0,0,0,0,0 },
	{ 0,1,1,1,2,2,2,2,2,2,2,2,2,2,1,0,0,0,0,0,0,0,0 },
	{ 0,0,1,2,2,1,1,1,1,2,2,2,2,1,0,0,0,0,0,0,0,0,0 },
	{ 0,0,0,1,1,2,2,2,2,1,2,2,1,2,1,0,0,0,0,0,0,0,0 },
	{ 0,0,0,0,1,2,1,2,1,2,2,1,2,2,2,1,0,0,0,0,0,0,0 },
	{ 0,0,0,1,2,1,2,1,1,2,2,1,2,2,2,2,1,0,0,0,0,0,0 },
	{ 0,0,0,1,1,2,2,2,2,2,1,2,2,2,2,2,2,1,0,0,0,0,0 },
	{ 0,0,0,0,1,1,2,1,1,1,2,2,2,2,2,1,2,1,0,0,0,0,0 },
	{ 0,0,0,0,0,0,1,1,2,2,1,2,2,2,2,1,2,2,1,0,0,0,0 },
	{ 0,0,0,0,0,0,0,0,1,2,2,1,2,2,2,1,2,2,1,0,0,0,0 },
	{ 0,0,0,0,0,0,0,0,1,2,2,2,1,2,2,1,2,2,2,1,0,0,0 },
	{ 0,0,0,0,0,0,0,0,1,2,2,2,1,2,2,1,2,2,2,1,0,0,0 },
	{ 0,0,0,0,0,0,0,1,2,2,2,1,2,2,1,2,2,1,1,1,0,0,0 },
	{ 0,0,0,0,0,0,0,1,2,2,2,1,1,2,2,1,1,1,2,1,0,0,0 },
	{ 0,0,0,0,0,0,0,0,1,1,2,1,2,1,1,1,2,2,2,1,0,0,0 },
	{ 0,0,0,0,0,0,0,1,2,2,1,2,2,2,1,2,2,2,2,1,0,0,0 },
	{ 0,0,0,0,0,0,0,1,2,2,1,2,2,2,1,1,2,2,2,1,0,0,0 },
	{ 0,0,0,0,0,0,0,1,2,2,1,2,2,2,2,1,2,2,1,1,0,0,0 },
	{ 0,0,0,0,0,0,0,0,1,1,2,1,1,1,1,1,2,2,2,1,1,0,0 },
	{ 0,0,0,0,0,0,0,0,0,0,1,2,2,2,1,2,2,2,2,2,1,1,0 },
	{ 0,0,0,0,0,0,0,0,0,1,2,2,2,2,1,1,1,2,2,2,2,1,0 },
	{ 0,0,0,0,0,0,0,0,0,0,1,1,1,2,1,2,2,1,1,2,2,2,1 },
	{ 0,0,0,0,0,0,0,0,0,1,2,2,2,1,2,2,2,2,2,1,2,2,1 },
	{ 0,0,0,0,0,0,0,0,0,1,2,2,2,1,2,2,2,2,1,1,1,1,0 },
	{ 0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,1,1,0,0,0,0 }
};

const int SPRITEZOMBIE2[28][18] = {
    { 0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0 },
    { 0,0,0,0,1,1,1,1,1,0,0,1,0,0,0,0,0,0 },
    { 1,1,0,1,2,2,2,2,2,1,1,0,0,0,0,0,0,0 },
    { 0,0,1,2,2,2,2,2,2,2,2,1,0,0,0,0,0,0 },
    { 0,1,2,2,2,2,1,1,1,2,2,1,1,1,0,0,0,0 },
    { 0,1,2,2,2,1,2,2,2,1,2,1,0,0,0,0,0,0 },
    { 0,1,1,2,2,1,2,1,2,1,2,2,1,0,0,0,0,0 },
    { 1,2,2,1,2,2,1,2,2,1,2,2,1,1,0,0,0,0 },
    { 1,2,1,2,1,2,2,1,1,2,2,1,0,0,0,0,0,0 },
    { 0,1,2,2,1,2,2,2,2,2,2,1,0,0,0,0,0,0 },
    { 0,0,1,1,2,1,1,2,2,2,1,1,0,0,0,0,0,0 },
    { 0,0,0,0,1,2,2,1,2,1,2,2,1,0,0,0,0,0 },
    { 0,0,0,1,2,2,1,2,1,2,2,2,2,1,0,0,0,0 },
    { 0,0,0,0,1,1,1,1,2,2,1,2,2,1,0,0,0,0 },
    { 0,0,0,0,0,1,2,2,1,2,1,2,1,2,1,0,0,0 },
    { 0,0,0,0,0,0,1,2,2,1,2,2,1,2,1,0,0,0 },
    { 0,0,0,0,0,0,1,2,2,1,2,2,1,2,2,1,0,0 },
    { 0,0,0,0,0,0,1,2,2,1,2,1,2,2,1,1,0,0 },
    { 0,0,0,0,0,1,2,2,1,1,2,2,1,1,2,1,0,0 },
    { 0,0,0,0,0,0,1,1,2,2,1,2,1,2,2,1,0,0 },
    { 0,0,0,0,0,1,2,2,1,2,2,1,2,2,2,1,0,0 },
    { 0,0,0,0,0,1,2,2,1,2,2,2,1,2,2,1,0,0 },
    { 0,0,0,0,0,0,1,1,2,1,1,1,1,2,2,1,0,0 },
    { 0,0,0,0,0,0,0,0,1,2,2,1,2,2,2,2,1,0 },
    { 0,0,0,0,0,0,0,1,2,1,2,1,1,1,2,2,2,1 },
    { 0,0,0,0,0,0,0,1,2,2,1,2,2,2,1,2,2,1 },
    { 0,0,0,0,0,0,0,1,2,2,1,2,2,2,1,1,1,0 },
    { 0,0,0,0,0,0,0,0,1,1,0,1,1,1,0,0,0,0 }
  };

const int SPRITEZOMBIE3[21][14]= {
	{ 0,0,0,0,0,1,0,0,0,0,0,0,0,0 },
	{ 0,1,0,0,1,1,1,1,1,0,1,0,0,0 },
	{ 0,0,1,1,2,2,2,2,2,1,0,0,0,0 },
	{ 0,1,2,2,2,2,1,1,2,1,1,0,0,0 },
	{ 0,1,1,2,2,1,2,2,1,2,1,1,0,0 },
	{ 1,2,2,1,2,1,1,2,1,2,1,0,0,0 },
	{ 1,1,2,1,2,2,1,1,2,1,0,0,0,0 },
	{ 0,1,1,2,1,1,2,2,2,1,0,0,0,0 },
	{ 0,0,0,1,2,2,1,1,1,1,0,0,0,0 },
	{ 0,0,0,1,1,1,2,1,2,2,1,0,0,0 },
	{ 0,0,0,0,0,1,1,2,2,2,1,1,0,0 },
	{ 0,0,0,0,0,1,2,1,2,1,2,1,0,0 },
	{ 0,0,0,0,0,1,2,1,2,1,2,2,1,0 },
	{ 0,0,0,0,1,2,2,1,2,1,2,1,1,0 },
	{ 0,0,0,0,1,1,1,1,1,2,1,2,1,0 },
	{ 0,0,0,1,2,2,1,2,2,1,2,2,1,0 },
	{ 0,0,0,0,1,1,1,1,1,1,2,2,1,0 },
	{ 0,0,0,0,0,0,1,2,2,1,2,2,1,0 },
	{ 0,0,0,0,0,0,1,1,2,1,1,2,2,1 },
	{ 0,0,0,0,0,1,2,2,1,2,2,1,1,1 },
	{ 0,0,0,0,0,1,1,1,0,1,1,0,0,0 }
};

const int SPRITEZOMBIE4[14][9]= {
    { 0,0,1,1,1,0,0,0,0 },
    { 0,1,2,2,2,1,0,0,0 },
    { 1,2,2,2,2,2,1,0,0 },
    { 1,2,1,2,1,2,1,0,0 },
    { 1,2,2,2,2,1,0,0,0 },
    { 1,1,2,1,2,1,1,0,0 },
    { 0,1,1,1,1,2,1,0,0 },
    { 0,0,1,2,1,2,1,1,0 },
    { 0,0,0,1,2,2,2,1,0 },
    { 0,0,1,2,1,2,1,1,0 },
    { 0,0,1,1,2,1,2,1,1 },
    { 0,0,0,1,2,1,1,2,1 },
    { 0,0,1,2,2,1,2,1,1 },
    { 0,0,0,1,1,0,1,1,0 }
  };



#endif