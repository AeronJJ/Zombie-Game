#include "Player.h"

Player::Player() {
  moveEntity(Coord3D (0.5,0,0.5));
  currentScene_ = nullptr;
  setOffset_(8,8);
  playerSprite_.cols = 17;
  playerSprite_.rows = 15;
  playerSprite_.data = (int*)CROSSHAIR;
  setSprite(&playerSprite_);  
}

Player::~Player() {
  currentScene_ = nullptr;
}

void Player::update() {
  if (!currentScene_->checkBounds(getPosition())) {

  }
}

void Player::updateScene(Scene* scn) {
  currentScene_ = scn;
}

Scene* Player::getScene() {
  return currentScene_;
}

void Player::shiftEntity(Coord3D newPos) {
  Coord3D curPos = getPosition();
  
  newPos.x += curPos.x;
  newPos.y += curPos.y;
  newPos.z += curPos.z;
  Coord3D* bounds = currentScene_->getSize();

  if (newPos.x > bounds->x) newPos.x = bounds->x;
  else if (newPos.x < 0) newPos.x = 0;
  if (newPos.z > bounds->z - offset_.y/48) newPos.z = bounds->z - offset_.y/48;
  else if (newPos.z < 0 - offset_.y/48) newPos.z = 0 - offset_.y/48;

  moveEntity(newPos);
}