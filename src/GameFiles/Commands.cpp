#include "Commands.h"
#include <cstdio>


// All execute functions need to verify that entity is not null!!!!

moveEntity::moveEntity(Entity* entity) : JoystickAction(entity) {}
moveEntityBack::moveEntityBack(Entity* entity) : Action(entity) {}
moveEntityForwards::moveEntityForwards(Entity* entity) : Action(entity) {}
moveEntityLeft::moveEntityLeft(Entity* entity) : Action(entity) {}
moveEntityRight::moveEntityRight(Entity* entity) : Action(entity) {}
shootEntity::shootEntity(Messenger* mssngr, Entity* entity) : Action(entity), mssngr_(mssngr) {}
previousScene::previousScene(Player* entity) : Action(entity), player_(entity) {}

void moveEntity::Execute() {
  Coord3D newPos(jsPos_.x*movementSpeed_, 0, jsPos_.y*movementSpeed_);
  entity_->shiftEntity(newPos);
}

void moveEntityBack::Execute() {
  entity_->shiftEntity(Coord3D (0,movementSpeed_,0));
}

void moveEntityForwards::Execute() {
  entity_->shiftEntity(Coord3D (0,-movementSpeed_,0));
}

void moveEntityLeft::Execute() {
  entity_->shiftEntity(Coord3D (-movementSpeed_,0,0));
}

void moveEntityRight::Execute() {
  entity_->shiftEntity(Coord3D (movementSpeed_,0,0));
}

void shootEntity::Execute() {
  mssngr_->Notify(EventMSG::EVENT_GUN_SHOT);
}

previousScene::~previousScene() {
  player_ = nullptr;
}

void previousScene::Execute() {
  player_->getScene()->goToScene(0);
}

rightWindow::rightWindow(Player* player) : Action(player), player_(player) {}

void rightWindow::Execute() {
  player_->getScene()->goToScene(1);
}

leftWindow::leftWindow(Player* player) : Action(player), player_(player) {}

leftWindow::~leftWindow() {
  player_ = nullptr; // Unnecessary
}

void leftWindow::Execute() {
  // Need a way to check if it's of the GameScene type before allowing changing scene.
  //Scene* scn = player_->getScene();
  //if(dynamic_cast<GameScene*>(scn) != nullptr)
  player_->getScene()->goToScene(2);
}

pauseAction::pauseAction(Messenger* mssngr) : Action(nullptr), mssngr_(mssngr) {}

void pauseAction::Execute() {
  mssngr_->Notify(EventMSG::EVENT_PAUSE_GAME);
}

backAction::backAction(Player* player) : Action(player), player_(player) {}

void backAction::Execute() {
  player_->getScene()->goToScene(0);
}