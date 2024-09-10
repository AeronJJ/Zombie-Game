#pragma once

#include <SDL.h>
#include <map>
#include "mbed.h" // BUTTONLIST
#include "KeyboardConfig.h"

#include <iostream>

class SDLInputHandling {
 public:
  SDLInputHandling();
  bool checkInputs();
 private:
  void init_();
  void fillMap_();
  void setButton(int buttonEnumVal, bool pressed);
  void setAnalog(int analogEnumVal, float val);
  bool quit_ = false;
  SDL_Event e_;
  std::map<int, int> keyMap_; // key to pin values.
  std::map<int, int> analogKeyMap_;
  std::map<int, int> pinToIndex_;
  int maxInputs_;
  DigitalIn** digitals_;
  AnalogIn** analogs_;
  bool initialised_;
};
