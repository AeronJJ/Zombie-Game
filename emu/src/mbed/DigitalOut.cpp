#include "DigitalOut.h"

DigitalOut::DigitalOut(PinName pin) { }
DigitalOut::DigitalOut(PinName pin, int value) {
  val_ = value;
}

void DigitalOut::write(int value) {
  val_ = value;
}

int DigitalOut::read() {
  return val_;
}

int DigitalOut::is_connected() {
  return 1;
}

DigitalOut &DigitalOut::operator= (int value) {
  write(val_);
  return *this;
}

DigitalOut &DigitalOut::operator= (DigitalOut &rhs) {
  write(rhs.read());
  return *this;
}

DigitalOut::operator int() {
  return read();
}
