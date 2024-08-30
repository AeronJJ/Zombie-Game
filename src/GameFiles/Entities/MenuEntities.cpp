#include "MenuEntities.h"
MenuSpriteGroup::MenuSpriteGroup() : titleSprite(11, 35, (int*)TITLE), startSprite(7, 31, (int*)START), startSprite_S(7, 31, (int*)START_S), optionSprite(7, 42, (int*)OPTIONS), optionSprite_S(7, 42, (int*)OPTIONS_S),
                                     fpsSprite(7, 57, (int*)FPS), fpsSprite_S(7, 57, (int*)FPS_S), dbgmemSprite(7, 75, (int*)DBGMEM), dbgmemSprite_S(7, 75, (int*)DBGMEM_S), remapSprite(7, 69, (int*)REMAP), remapSprite_S(7, 69, (int*) REMAP_S),
                                     checkBoxFilledSprite(7, 7, (int*)CHECKBOXFILLED), checkBoxFilledSprite_S(7, 7, (int*)CHECKBOXFILLED_S), checkBoxEmptySprite(7, 7, (int*)CHECKBOXEMPTY), checkBoxEmptySprite_S(7, 7, (int*)CHECKBOXEMPTY_S)
                                     {}


MenuEntityBase::MenuEntityBase(MenuSpriteGroup* sprGrp, Messenger* messenger) : spriteGroup_(sprGrp), Entity(messenger) {

}

void MenuEntityBase::update() {
  if(focused_) {
    if(!s_) {
      s_ = !s_;
      if (togglable_) {
        if (toggled_ && currentSprite_ != 3) {
          currentSprite_ = 3;
          combineSprites_(spr_s, &spriteGroup_->checkBoxFilledSprite_S, true);
        }
        else if (!toggled_ && currentSprite_ != 2) {
          currentSprite_ = 2;
          combineSprites_(spr_s, &spriteGroup_->checkBoxEmptySprite_S, true);
        }
        setSprite(&combinedSprite_);
      }
      else {
        setSprite(spr_s);
      }
    }
  }
  else {
    s_ = false;
    if (togglable_) {
      if (toggled_ && currentSprite_ != 1) {
        currentSprite_ = 1;
        combineSprites_(spr, &spriteGroup_->checkBoxFilledSprite, false);
      }
      else if (!toggled_ && currentSprite_ != 0) {
        currentSprite_ = 0;
        combineSprites_(spr, &spriteGroup_->checkBoxEmptySprite, false);
      }
      setSprite(&combinedSprite_);
    }
    else {
      setSprite(spr);
    }
  }
  customUpdate();
}

void MenuEntityBase::shot() {
  goToScene_ = shotScene_;
}

void MenuEntityBase::combineSprites_(Sprite* spr1, Sprite* spr2, bool s) {
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
  sprData_.resize((x1+x2)*y1);
  sprData_ = newSprite;

  combinedSprite_.rows = y1;
  combinedSprite_.cols = x1+x2;
  combinedSprite_.data = (int*)sprData_.data();

}

void MenuEntityBase::customUpdate() {}

Title::Title(MenuSpriteGroup* sprGrp) : spriteGroup_(sprGrp) {
  moveEntity(Coord3D (0.3,0.01,0.7));
  setSprite(&spriteGroup_->titleSprite);
}

StartEntity::StartEntity(MenuSpriteGroup* sprGrp) : MenuEntityBase(sprGrp, nullptr) {
  moveEntity(Coord3D (0.3,0.01,0.45));
  spr = &spriteGroup_->startSprite;
  spr_s = &spriteGroup_->startSprite_S;
  setSprite(spr);
  shotScene_ = 2;
}

OptionsEntity::OptionsEntity(MenuSpriteGroup* sprGrp) : MenuEntityBase(sprGrp, nullptr)  {
  moveEntity(Coord3D (0.3,0.01,0.3));
  spr = &spriteGroup_->optionSprite;
  spr_s = &spriteGroup_->optionSprite_S;
  setSprite(spr);
  shotScene_ = 1;
}

FpsOptionEntity::FpsOptionEntity(MenuSpriteGroup* sprGrp, Messenger* messenger) : MenuEntityBase(sprGrp, messenger){
  moveEntity(Coord3D (0.01,0.01,0.7));
  spr = &spriteGroup_->fpsSprite;
  spr_s = &spriteGroup_->fpsSprite_S;
  setSprite(spr);
  //shotScene_ = 1;
  justification_ = 0;
  togglable_ = true;
}

void FpsOptionEntity::shot() {
  messenger_->Notify(EventMSG::EVENT_TOGGLE_FPS);
  toggled_ = !toggled_;
  s_ = false; // Need to say that sprite needs updating, shoddy, but works.
}

DBGOptionEntity::DBGOptionEntity(MenuSpriteGroup* sprGrp, Messenger* messenger) : MenuEntityBase(sprGrp, messenger) {
  moveEntity(Coord3D (0.01,0.01,0.5));
  spr = &spriteGroup_->dbgmemSprite;
  spr_s = &spriteGroup_->dbgmemSprite_S;
  setSprite(spr);
  //shotScene_ = 1;
  justification_ = 0;
  togglable_ = true;
}

void DBGOptionEntity::shot() {
  messenger_->Notify(EventMSG::EVENT_TOGGLE_DBG);
  toggled_ = !toggled_;
  s_ = false; // Need to say that sprite needs updating, shoddy, but works.
}

RemapOptionEntity::RemapOptionEntity(MenuSpriteGroup* sprGrp, Messenger* mssngr) : MenuEntityBase(sprGrp, mssngr) {
  moveEntity(Coord3D (0.01,0.01,0.32));
  spr = &spriteGroup_->remapSprite;
  spr_s = &spriteGroup_->remapSprite_S;
  setSprite(spr);
  //shotScene_ = 1;
  justification_ = 0;
}

void RemapOptionEntity::shot() {
  messenger_->Notify(EventMSG::EVENT_REMAP_BUTTONS);
}