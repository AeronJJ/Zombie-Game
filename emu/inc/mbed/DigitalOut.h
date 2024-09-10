#pragma once

#include "Inputs.h"

class DigitalOut {
public:
  DigitalOut(PinName pin);
  DigitalOut(PinName pin, int value);
  
  void write(int value);
  int read();
  int is_connected();
    
  DigitalOut &operator= (int value);/* {
    // Underlying write is thread safe
    write(value);
    return *this;
    };*/

  DigitalOut &operator= (DigitalOut &rhs);

  operator int(); /*{
    // Underlying call is thread safe
    return read();
    };*/

private:
  int val_;
};
