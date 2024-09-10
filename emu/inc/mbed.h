#pragma once

// This file replaces simple functionality included in Mbed OS to create compatibility with SDL

#include "Timer.h"
#include "STM32L4.h"
#include "PinNameAliases.h"
#include <cstdio>
#include <cmath>

enum PinMode {
  PullUp,
  PullDown,
  PullNone,
  OpenDrain
};

class DigitalIn {
public:
  DigitalIn();
  DigitalIn(PinName pin);
  ~DigitalIn();

  bool read();
  void set(bool io);
  void mode(PinMode mode);
  PinName getPin();
  
private:
  bool pressed_ = 1;
  PinMode mode_ = PullUp;
  PinName pin_;
};


class AnalogIn {
public:
  AnalogIn();
  AnalogIn(PinName pin);
  ~AnalogIn();
  float read();
  void set(float io);
  PinName getPin();
private:
  float val_ = 0.5;
  PinName pin_;
};


class IOContainer {
public:
  IOContainer();
  void addDigitalIn(DigitalIn* obj);
  void removeDigitalIn(DigitalIn* obj);
  void addAnalogIn(AnalogIn* obj);
  void removeAnalogIn(AnalogIn* obj);
  DigitalIn** getDigitals();
  AnalogIn** getAnalogs();
  int getMaxInputs();

  bool remapRequired();

private:
  void sortDigitals_();
  DigitalIn** digitals_;
  const int maxInputs_ = 20;
  int nextDigitalFree_;

  //void sortAnalogs_();
  AnalogIn** analogs_;
  int nextAnalogFree_;

  bool remapRequired_ = false;
};

extern IOContainer* BUTTONLIST;
