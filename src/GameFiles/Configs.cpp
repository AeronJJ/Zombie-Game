#include "Configs.h"

MenuInputConfig::MenuInputConfig(Player* player, Messenger* mssngr) : js_(player), mssngr_(mssngr), shoot_(mssngr), back_(player) {
  jsAction_ = &js_;
  buttonActions_[0] = &shoot_;
  buttonActions_[1] = nullptr;
  buttonActions_[2] = &back_; // Back
  buttonActions_[3] = nullptr;
  buttonActions_[4] = &shoot_;
  buttonActions_[5] = nullptr;

  js_.setMovementSpeed(0.02);
}

MenuInputConfig::~MenuInputConfig() {

}


GameInputConfig::GameInputConfig(Player* player, Messenger* mssngr) : js_(player), shoot_(mssngr), left_(player), right_(player), pause_(mssngr), mssngr_(mssngr) {
  jsAction_ = &js_;
  js_.setMovementSpeed(0.02);

  resetInputs();
}

void GameInputConfig::mapLeft(int i) {
  buttonActions_[i] = &left_;
}

void GameInputConfig::mapPause(int i) {
  buttonActions_[i] = &pause_;
}

void GameInputConfig::mapShoot(int i) {
  buttonActions_[i] = &shoot_;
}

void GameInputConfig::mapRight(int i) {
  buttonActions_[i] = &right_;
}

void GameInputConfig::resetInputs() {
  buttonActions_[0] = &shoot_;
  buttonActions_[1] = nullptr;
  buttonActions_[2] = &pause_;
  buttonActions_[3] = &left_;
  buttonActions_[4] = &shoot_;
  buttonActions_[5] = &right_;
}