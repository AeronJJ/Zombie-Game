#include "RemapScene.h"

RemapCommandScene::RemapCommandScene(RemapSpriteGroup* sprGrp, Player* player, InputConfig* config) : Scene(Coord3D (0,0,0), Coord3D (1,1,1), player, config), sprGrp_(sprGrp) {
  shootButt_ = new ShootButtonEntity(sprGrp_, nullptr);
  leftButt_ = new GoLeftButtonEntity(sprGrp_, nullptr);
  rightButt_ = new GoRightButtonEntity(sprGrp_, nullptr);
  pauseButt_ = new PauseButtonEntity(sprGrp_, nullptr);

  addEntity(shootButt_);
  addEntity(leftButt_);
  addEntity(rightButt_);
  addEntity(pauseButt_);
}

RemapCommandScene::~RemapCommandScene() {
  delete shootButt_;
  delete leftButt_;
  delete rightButt_;
  delete pauseButt_;
}

Scene* RemapCommandScene::update() {
  if (shootButt_->shot_) {
    commandToMap = shootButt_->command_;
    goToScene(0);
  }
  else if (leftButt_->shot_) {
    commandToMap = leftButt_->command_;
    goToScene(0);
  }
  else if (rightButt_->shot_) {
    commandToMap = rightButt_->command_;
    goToScene(0);
  }
  else if (pauseButt_->shot_) {
    commandToMap = pauseButt_->command_;
    goToScene(0);
  }
  internalUpdate_();

  if (validateSceneIndex_(goToSceneFlag_)) {
    int index = goToSceneFlag_;
    goToSceneFlag_ = -1;
    return getScene(index);
  }
  else {
    return nullptr;
  }
}


RemapButtonScene::RemapButtonScene(RemapSpriteGroup* sprGrp, Player* player, InputConfig* config, Messenger* mssngr) : Scene(Coord3D (0,0,0), Coord3D (1,1,1), player, config), sprGrp_(sprGrp), player_(player), mssngr_(mssngr) {
  defaults_ = new LoadDefaultsEntity(sprGrp_, nullptr);
  butt1_ = new Button1Entity(sprGrp_, nullptr);
  butt2_ = new Button2Entity(sprGrp_, nullptr);
  butt3_ = new Button3Entity(sprGrp_, nullptr);
  butt4_ = new Button4Entity(sprGrp_, nullptr);
  butt5_ = new Button5Entity(sprGrp_, nullptr);
  diag_ = new DiagramEntity(sprGrp_);

  addEntity(defaults_);
  addEntity(butt1_);
  addEntity(butt2_);
  addEntity(butt3_);
  addEntity(butt4_);
  addEntity(butt5_);
  addEntity(diag_);
  sortEntities();
}

RemapButtonScene::~RemapButtonScene() {
  delete defaults_;
  delete butt1_;
  delete butt2_;
  delete butt3_;
  delete butt4_;
  delete butt5_;
}

Scene* RemapButtonScene::update() {
  internalUpdate_();
  if (commandScene_ != nullptr) {
    commandToMap = commandScene_->commandToMap;
  }
  if (commandToMap != CommandMSG::COMMAND_NULL) {
    destroyCommandScene_();
    mssngr_->Notify(EventMSG::EVENT_REMAP_COMPLETED);
    goToScene(0);
  }
  if (defaults_->shot_) {
    defaults_->shot_ = !defaults_->shot_;
    buttonToMap = defaults_->button_;
    mssngr_->Notify(EventMSG::EVENT_REMAP_COMPLETED);
    goToScene(0);
  }
  else if (butt1_->shot_) {
    butt1_->shot_ = !butt1_->shot_;
    buttonToMap = butt1_->button_;
    goToCommandScene_();
  }
  else if (butt2_->shot_) {
    butt2_->shot_ = !butt2_->shot_;
    buttonToMap = butt2_->button_;
    goToCommandScene_();
  }
  else if (butt3_->shot_) {
    butt3_->shot_ = !butt3_->shot_;
    buttonToMap = butt3_->button_;
    goToCommandScene_();
  }
  else if (butt4_->shot_) {
    butt4_->shot_ = !butt4_->shot_;
    buttonToMap = butt4_->button_;
    goToCommandScene_();
  }
  else if (butt5_->shot_) {
    butt5_->shot_ = !butt5_->shot_;
    buttonToMap = butt5_->button_;
    goToCommandScene_();
  }
  if (validateSceneIndex_(goToSceneFlag_)) {
    int index = goToSceneFlag_;
    goToSceneFlag_ = -1;
    return getScene(index);
  }
  else {
    return nullptr;
  }
}

void RemapButtonScene::goToCommandScene_() {
  commandScene_ = new RemapCommandScene(sprGrp_, player_, getInputConfig());
  setScene(1, commandScene_);
  commandScene_->setScene(0, this);
  goToScene(1);
}

void RemapButtonScene::destroyCommandScene_() {
  delete commandScene_;
  commandScene_ = nullptr;
}