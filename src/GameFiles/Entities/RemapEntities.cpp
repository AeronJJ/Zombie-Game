#include "RemapEntities.h"

RemapSpriteGroup::RemapSpriteGroup() : loadDefaultSprite(7, 75, (int*)LOADDEFAULTS), loadDefaultSprite_S(7, 75, (int*)LOADDEFAULTS_S), button1Sprite(7, 43, (int*)BUTTONSPRITE1), 
                                       button1Sprite_S(7, 43, (int*)BUTTONSPRITE1_S), button2Sprite(7, 43, (int*)BUTTONSPRITE2), button2Sprite_S(7, 43, (int*)BUTTONSPRITE2_S), 
                                       button3Sprite(7, 43, (int*)BUTTONSPRITE3), button3Sprite_S(7, 43, (int*)BUTTONSPRITE3_S), button4Sprite(7, 43, (int*)BUTTONSPRITE4), 
                                       button4Sprite_S(7, 43, (int*)BUTTONSPRITE4_S), button5Sprite(7, 43, (int*)BUTTONSPRITE5), button5Sprite_S(7, 43, (int*)BUTTONSPRITE5_S), 
                                       shootSprite(7, 31, (int*)SHOOT), shootSprite_S(7, 31, (int*)SHOOT_S), goLeftSprite(7, 39, (int*)GOLEFT), goLeftSprite_S(7, 39, (int*)GOLEFT_S), 
                                       goRightSprite(7, 45, (int*)GORIGHT), goRightSprite_S(7, 45, (int*)GORIGHT_S), pauseSprite(7, 31, (int*)PAUSE), pauseSprite_S(7, 31, (int*)PAUSE_S),
                                       diagramSprite(21, 32, (int*)DIAGRAM) 
{

}

RemapEntityBase::RemapEntityBase(RemapSpriteGroup* sprGrp, Messenger* mssngr) : Entity(mssngr) {
  button_ = ButtonMSG::BUTTON_NULL;
  command_ = CommandMSG::COMMAND_NULL;
  spr_ = &sprGrp->loadDefaultSprite;
  spr_S_ = &sprGrp->loadDefaultSprite_S;
}

void RemapEntityBase::update() {
  if(focused_) {
    if(!s_) {
      s_ = !s_;
      setSprite(spr_S_);
    }
  }
  else {
    s_ = false;
    setSprite(spr_);
  }
}

void RemapEntityBase::shot() {
  shot_ = true;
}

LoadDefaultsEntity::LoadDefaultsEntity(RemapSpriteGroup* sprGrp, Messenger* mssngr) : RemapEntityBase(sprGrp, mssngr) {
  moveEntityByPixel(4, 46);
  setJustification(0);
  spr_ = &sprGrp->loadDefaultSprite;
  spr_S_ = &sprGrp->loadDefaultSprite_S;
  setSprite(spr_);
  button_ = ButtonMSG::BUTTON_DEFAULTS;
}

Button1Entity::Button1Entity(RemapSpriteGroup* sprGrp, Messenger* mssngr) : RemapEntityBase(sprGrp, mssngr) {
  moveEntityByPixel(4, 11);
  setJustification(0);
  spr_ = &sprGrp->button1Sprite;
  spr_S_ = &sprGrp->button1Sprite_S;
  setSprite(spr_);
  button_ = ButtonMSG::BUTTON_1;
}

Button2Entity::Button2Entity(RemapSpriteGroup* sprGrp, Messenger* mssngr) : RemapEntityBase(sprGrp, mssngr) {
  moveEntityByPixel(4, 18);
  setJustification(0);
  spr_ = &sprGrp->button2Sprite;
  spr_S_ = &sprGrp->button2Sprite_S;
  setSprite(spr_);
  button_ = ButtonMSG::BUTTON_2;
}

Button3Entity::Button3Entity(RemapSpriteGroup* sprGrp, Messenger* mssngr) : RemapEntityBase(sprGrp, mssngr) {
  moveEntityByPixel(4, 25);
  setJustification(0);
  spr_ = &sprGrp->button3Sprite;
  spr_S_ = &sprGrp->button3Sprite_S;
  setSprite(spr_);
  button_ = ButtonMSG::BUTTON_3;
}

Button4Entity::Button4Entity(RemapSpriteGroup* sprGrp, Messenger* mssngr) : RemapEntityBase(sprGrp, mssngr) {
  moveEntityByPixel(4, 32);
  setJustification(0);
  spr_ = &sprGrp->button4Sprite;
  spr_S_ = &sprGrp->button4Sprite_S;
  setSprite(spr_);
  button_ = ButtonMSG::BUTTON_4;
}

Button5Entity::Button5Entity(RemapSpriteGroup* sprGrp, Messenger* mssngr) : RemapEntityBase(sprGrp, mssngr) {
  moveEntityByPixel(4, 39);
  setJustification(0);
  spr_ = &sprGrp->button5Sprite;
  spr_S_ = &sprGrp->button5Sprite_S;
  setSprite(spr_);
  button_ = ButtonMSG::BUTTON_5;
}

ShootButtonEntity::ShootButtonEntity(RemapSpriteGroup* sprGrp, Messenger* mssngr) : RemapEntityBase(sprGrp, mssngr) {
  moveEntityByPixel(4, 15);
  setJustification(0);
  spr_ = &sprGrp->shootSprite;
  spr_S_ = &sprGrp->shootSprite_S;
  setSprite(spr_);
  command_ = CommandMSG::COMMAND_SHOOT;
}

GoLeftButtonEntity::GoLeftButtonEntity(RemapSpriteGroup* sprGrp, Messenger* mssngr) : RemapEntityBase(sprGrp, mssngr) {
  moveEntityByPixel(4, 25);
  setJustification(0);
  spr_ = &sprGrp->goLeftSprite;
  spr_S_ = &sprGrp->goLeftSprite_S;
  setSprite(spr_);
  command_ = CommandMSG::COMMAND_GO_LEFT;
}

GoRightButtonEntity::GoRightButtonEntity(RemapSpriteGroup* sprGrp, Messenger* mssngr) : RemapEntityBase(sprGrp, mssngr) {
  moveEntityByPixel(4, 35);
  setJustification(0);
  spr_ = &sprGrp->goRightSprite;
  spr_S_ = &sprGrp->goRightSprite_S;
  setSprite(spr_);
  command_ = CommandMSG::COMMAND_GO_RIGHT;
}

PauseButtonEntity::PauseButtonEntity(RemapSpriteGroup* sprGrp, Messenger* mssngr) : RemapEntityBase(sprGrp, mssngr) {
  moveEntityByPixel(4, 45);
  setJustification(0);
  spr_ = &sprGrp->pauseSprite;
  spr_S_ = &sprGrp->pauseSprite_S;
  setSprite(spr_);
  command_ = CommandMSG::COMMAND_PAUSE;
}

DiagramEntity::DiagramEntity(RemapSpriteGroup* sprGrp) {
  moveEntityByPixel(50, 37);
  setJustification(0);
  setSprite(&sprGrp->diagramSprite);
}