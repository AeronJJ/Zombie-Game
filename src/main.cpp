#include "mbed.h"
#include "ZombieGameEngine.h"
//#include "mbed_mem_trace.h"

int main() {
  //mbed_mem_trace_set_callback(mbed_mem_trace_default_callback);

  ZombieGameEngine game;

  while(true) {
    game.run();
  }
}


