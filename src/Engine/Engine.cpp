#include "Engine.h"

Engine::Engine() 
        : lcd_(PC_7, PA_9, PB_10, PB_5, PB_3, PA_10), renderer_(nullptr, &lcd_),  joystick_(PC_0, PC_1), 
        button0_(A3), button1_(PC_13), button2_(PA_11), button3_(PB_12), button4_(PB_11), button5_(PB_2), 
        inputHandler_(&bootTime_, &joystick_, &button0_, &button1_, &button2_, &button3_, &button4_, &button5_, nullptr)  
{
    init_();
    customInit_();
    button2_.mode(PullUp);
    button3_.mode(PullUp);
    button4_.mode(PullUp);
    button5_.mode(PullUp);
}

void Engine::run() {
    // Timing:
    resetLoop_();
    if (serialFPS_) {
        calcFPS_();
    }
    if (dbgMem_) {
        print_memory_info_();
    }
    // Rendering:
    renderer_.render();
    currentScene_ = renderer_.getScene();
    newScene_ = currentScene_->update();

    // Inputs:
    inputHandler_.HandleInputs();

    // Game Specific Logic:
    customLoopLogic_();
}

void Engine::ToggleFPSCounter() { serialFPS_ = !serialFPS_; }
void Engine::ToggleDBGMem() { dbgMem_ = !dbgMem_; }

void Engine::customLoopLogic_() {}
void Engine::customInit_() {}

void Engine::init_() {
    joystick_.init();
    lcd_.init(LPH7366_1);        //initialise for LPH7366-1 LCD (Options are LPH7366_1 and LPH7366_6)
    lcd_.setContrast(0.5);      //set contrast to 50%
    lcd_.setBrightness(0.9);     //set brightness to 50% (utilises the PWM)

    loopTime_.start();
    bootTime_.start();
}

void Engine::resetLoop_() {
    loopTime_.stop();
    msDelay_ = std::chrono::duration_cast<std::chrono::milliseconds>(periodus_ - loopTime_.elapsed_time());
    if (msDelay_.count() < 0) {msDelay_ = 1ms;}
    ThisThread::sleep_for(msDelay_);
    usDelay_ = (periodus_-loopTime_.elapsed_time()).count() % 1000;
    if (usDelay_ < 0) {usDelay_ = 1;}
    wait_us(usDelay_);
    loopTime_.reset();
    loopTime_.start();
}

void Engine::calcFPS_() {
    loopCountFPS_++;
    if(loopCountFPS_ >= 10) {
      int newTime = bootTime_.elapsed_time().count();
      int frameTime = floor(10000000.0/(newTime - prevTime_));
      prevTime_ = newTime;
      printf("Current FPS: %i\n", frameTime);
      loopCountFPS_ = 0;
    }
}

void Engine::print_memory_info_() {
    /*
  // Code taken from here: https://os.mbed.com/blog/entry/Tracking-memory-usage-with-Mbed-OS/
    if (bootTime_.elapsed_time() > dbgMemCounter_ + 1000ms) {
        dbgMemCounter_ = bootTime_.elapsed_time();
        // allocate enough room for every thread's stack statistics
        int cnt = osThreadGetCount();
        mbed_stats_stack_t *stats = (mbed_stats_stack_t*) malloc(cnt * sizeof(mbed_stats_stack_t));

        cnt = mbed_stats_stack_get_each(stats, cnt);
        for (int i = 0; i < cnt; i++) {
            printf("Thread: 0x%X, Stack size: %u / %u\r\n", stats[i].thread_id, stats[i].max_size, stats[i].reserved_size);
        }
        free(stats);

        // Grab the heap statistics
        mbed_stats_heap_t heap_stats;
        mbed_stats_heap_get(&heap_stats);
        printf("Heap size: %u / %u bytes\r\n", heap_stats.current_size, heap_stats.reserved_size);
    }
    */
}


void Engine::invertLCD_() {
  inverted_ = !inverted_;
  if (inverted_) {
    lcd_.inverseMode();
  }
  else {
    lcd_.normalMode();
  }
}