#ifndef ENGINE_H
#define ENGINE_H

#include "Renderer.h"
#include "Joystick.h"
#include "InputHandler.h"
#include <chrono>

class Engine {
    public:
    Engine();
    
    void run();

    void ToggleFPSCounter();
    void ToggleDBGMem();

    protected:
    virtual void customLoopLogic_();
    virtual void customInit_();
    void invertLCD_();

    Timer bootTime_;

    Renderer renderer_;
    InputHandler inputHandler_;

    Scene* currentScene_ = nullptr;
    Scene* newScene_ = nullptr;

    private:
    void init_();
    void resetLoop_();
    void calcFPS_();
    void print_memory_info_();

    N5110 lcd_;
    
    Action* nextInput_ = nullptr;
    
    Timer loopTime_;
    
    int FPSTarget_ = 30;
    std::chrono::microseconds periodus_ = std::chrono::microseconds(1000000/FPSTarget_);
    std::chrono::milliseconds msDelay_ = 0ms;
    int usDelay_ = 0;

    Joystick joystick_;
    DigitalIn button0_; // Joystick button
    DigitalIn button1_;
    DigitalIn button2_;
    DigitalIn button3_;
    DigitalIn button4_;
    DigitalIn button5_;

    bool serialFPS_ = false; // Output FPS to serial every second
    bool dbgMem_ = false; // Output Memory info to serial every second
    std::chrono::microseconds dbgMemCounter_ = 0ms;
    int loopCountFPS_ = 0;
    int prevTime_ = 0;
    bool inverted_ = false;
};

#endif