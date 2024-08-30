#include "Entity.h"

Sprite::Sprite(int rows, int cols, int* data, bool reverse) : rows(rows), cols(cols), data(data), reverse(reverse) {}

Sprite::Sprite() : rows(0), cols(0), data(nullptr) {}

Entity::Entity(Messenger* messenger, bool createdByScene) : position_(0,0,0), messenger_(messenger), createdByScene_(createdByScene) {
  sprites_ = new Sprite*[maxSprites];
  for (int i = 0; i < maxSprites; i++) {
    sprites_[i] = nullptr;
  }
}

Entity::~Entity() {
  delete [] sprites_;
}

void Entity::update() {}

void Entity::setSprite(int row, int col, int* sprite, int scale) {
  sprites_[scale]->cols = col;
  sprites_[scale]->rows = row;
  sprites_[scale]->data = sprite;
}

void Entity::setSprite(int row, int col, int* sprite) {
  for (int i = 0; i < maxSprites; i++) {
    sprites_[i]->cols = col;
    sprites_[i]->rows = row;
    sprites_[i]->data = sprite;
  }
}

void Entity::setSprite(Sprite* sprite, int scale) {
  sprites_[scale] = sprite;
}

void Entity::setSprite(Sprite* sprite) {
  for (int i = 0; i < maxSprites; i++) {
    sprites_[i] = sprite;
  }
}

int Entity::getRows(int scale) {
  if (sprites_[scale] != nullptr) return sprites_[scale]->rows;
  else return 0;
}
int Entity::getCols(int scale) {
  if (sprites_[scale] != nullptr) return sprites_[scale]->cols;
  else return 0;  
}

int* Entity::getSpriteData(int scale) {
  if (sprites_[scale] != nullptr) return sprites_[scale]->data;
  else return nullptr;
}

Sprite* Entity::getSprite(int scale) {
  return sprites_[scale];
}

Coord3D Entity::getPosition() {
  return position_;
}

void Entity::moveEntity(Coord3D newPos) {
  position_ = newPos;
}

void Entity::shiftEntity(Coord3D mov) {
  position_.x += mov.x;
  position_.y += mov.y;
  position_.z += mov.z;
}

void Entity::moveEntityByPixel(double x, double y) {
  moveEntity(Coord3D (x/84, 0.01, 1-y/48));
}

void Entity::setRows(int row, int pos) {
  if (sprites_[pos] != nullptr) sprites_[pos]->rows = row;
}

void Entity::setCols(int col, int pos) {
  if (sprites_[pos] != nullptr) sprites_[pos]->cols = col;
}

void Entity::desetFocus() {focused_ = false;}

void Entity::setFocus() {focused_ = true;}

void Entity::setOffset_(int x, int y) {
  offset_.x = x;
  offset_.y = y;
}

void Entity::setOffset_(Coord3D ofs) {
  offset_ = ofs;
}

Coord3D Entity::getOffset() {
  return offset_;
}

void Entity::shot() {
  
}

int Entity::goToScene() {
  int scene = goToScene_;
  goToScene_ = -1;
  return scene;
}

int Entity::getNextFree() {
  return nextFree_;
}

void Entity::setNextFree(int next) {
  nextFree_ = next;
}

int Entity::getJustification() {
  return justification_;
}

void Entity::setJustification(int just) {
  justification_ = just;
}

void Entity::togglePause() {
  paused_ = !paused_;
}

bool Entity::ownedByScene() {
  return createdByScene_;
}