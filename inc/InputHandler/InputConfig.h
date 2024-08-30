#ifndef INPUGCONFIG_H
#define INPUGCONFIG_H

#include "Action.h"

class InputConfig {
  public:
  InputConfig();
  virtual ~InputConfig();
  Action** getActions();
  JoystickAction* getJSAction();

  protected:
  JoystickAction* jsAction_;
  Action** buttonActions_;
  int maxButtons_ = 6;
};


#endif