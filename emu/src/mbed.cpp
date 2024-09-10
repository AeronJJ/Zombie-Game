#include "mbed.h"

#include <iostream>
#include <algorithm>

//DigitalIn::DigitalIn(Keys key) : key(key) { }

IOContainer::IOContainer() {
  // Poor mans linked list - used for like the fifth time in this project
  // Now that I've said that, it's obvious to see that this data structure should be implemented with a template
  // TODO: Implement the below as a template. Or just use vectors...
  digitals_ = new DigitalIn*[maxInputs_];
  for (int i = 0; i < maxInputs_; i++) {
    digitals_[i] = nullptr;
  }
  nextDigitalFree_ = 0;
  //std::cout << "Digitals created\n";

  analogs_ = new AnalogIn*[maxInputs_];
  for (int i = 0; i < maxInputs_; i++) {
    analogs_[i] = nullptr;
  }
  nextAnalogFree_ = 0;
}

void IOContainer::addDigitalIn(DigitalIn* obj) {
  if (nextDigitalFree_ < maxInputs_) {
    digitals_[nextDigitalFree_] = obj;
    nextDigitalFree_++;
    remapRequired_ = true;
    ///std::cout << "DigitalIn object added in pos: " << nextDigitalFree_ << std::endl;
  }
}

void IOContainer::removeDigitalIn(DigitalIn* obj) {
  // This function is needed in case a DigitalIn object in the users code is deleted before the program quits so the keyboard handler doesn't call deleted memory.
  for (int i = 0; i < maxInputs_; i++) {
    if (digitals_[i] == obj) {
      digitals_[i] = nullptr;
      nextDigitalFree_--;
      remapRequired_ = true;
    }
  }
  sortDigitals_(); // This is actually a terrible (but hilarious) idea.
}

void IOContainer::sortDigitals_() {
  std::sort(digitals_, digitals_ + maxInputs_, [](DigitalIn* a, DigitalIn* b) { return (a != nullptr); });
}

void IOContainer::addAnalogIn(AnalogIn* obj) {
  if (nextAnalogFree_ < maxInputs_) {
    analogs_[nextAnalogFree_] = obj;
    nextAnalogFree_++;
    remapRequired_ = true;
  }
}

void IOContainer::removeAnalogIn(AnalogIn* obj) {
  for (int i = 0; i < maxInputs_; i++) {
    if (analogs_[i] == obj) {
      analogs_[i] = nullptr;
      remapRequired_ = true;
    }
  }
}

int IOContainer::getMaxInputs() {
  return maxInputs_;
}

DigitalIn** IOContainer::getDigitals() {
  return digitals_;
}

AnalogIn** IOContainer::getAnalogs() {
  return analogs_;
}

bool IOContainer::remapRequired() {
    bool temp = remapRequired_;
    remapRequired_ = false;
    return temp;
}


IOContainer* BUTTONLIST = nullptr; // Global object eww.

DigitalIn::DigitalIn() { }

DigitalIn::DigitalIn(PinName pin) : pin_(pin) {
  if (BUTTONLIST == nullptr) {
    BUTTONLIST = new IOContainer;
  }
  BUTTONLIST->addDigitalIn(this);
}


DigitalIn::~DigitalIn() {
  BUTTONLIST->removeDigitalIn(this);
}


bool DigitalIn::read() {
	//bool val = pressed_;
	//pressed_ = 0;
	//return val;
	return pressed_;
}

void DigitalIn::set(bool io) {
	pressed_ = io;
	//std::cout << "Button Set!\n";
}

void DigitalIn::mode(PinMode mode) {
  mode_ = mode;
}

PinName DigitalIn::getPin() {
  return pin_;
}


AnalogIn::AnalogIn() { }

AnalogIn::AnalogIn(PinName pin) : pin_(pin) {
  //std::cout << "AnalogIn Created\n";
  if (BUTTONLIST == nullptr) {
    BUTTONLIST = new IOContainer;
  }
  BUTTONLIST->addAnalogIn(this);
}

AnalogIn::~AnalogIn() {
  BUTTONLIST->removeAnalogIn(this);
}

float AnalogIn::read() {
	return val_;
}

void AnalogIn::set(float val) {
	val_ = val;
	//std::cout << "Analog set!\n";
}

PinName AnalogIn::getPin() {
  return pin_;
}

