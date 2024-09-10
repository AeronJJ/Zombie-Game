#include "mbed.h"
#include "ZombieGameEngine.h"
//#include "mbed_mem_trace.h"

//#include "SDLInputHandling.h"

//int main(int argc, char* args[]){
int main() {
  //mbed_mem_trace_set_callback(mbed_mem_trace_default_callback);

  ZombieGameEngine game;

  //SDLInputHandling inputs;
  
  //while(!inputs.checkInputs() && !inputs.checkInputs() && !inputs.checkInputs()) {
  while(true) {
    game.run();
  }
}


