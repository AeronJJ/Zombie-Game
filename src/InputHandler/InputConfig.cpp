#include "InputConfig.h"

InputConfig::InputConfig() {
  buttonActions_ = new Action*[maxButtons_];
  for (int i = 0; i < maxButtons_; i++) {
    buttonActions_[i] = nullptr;
  }
}

InputConfig::~InputConfig() {
  delete [] buttonActions_;
}

Action** InputConfig::getActions() {
  return buttonActions_;
}

JoystickAction* InputConfig::getJSAction() {
  return jsAction_;
}