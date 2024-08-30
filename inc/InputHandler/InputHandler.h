#ifndef INPUTHANDLER_H
#define INPUTHANDLER_H

#include "mbed.h"
#include "Action.h"
#include "Joystick.h"
#include <chrono>

class InputHandler {
    public:
    void HandleInputs();
    InputHandler(Timer* timer, Joystick* joystick, DigitalIn* button0, DigitalIn* button1, DigitalIn* button2, DigitalIn* button3, DigitalIn* button4, DigitalIn* button5, Action** defaultConfig);
    ~InputHandler();

    void changeConfig(Action** newConfig, JoystickAction* jsConf);

    void bindButton(Action*, int num);
    void bindJoystick(JoystickAction*);

    private:
    Timer* delayTimer;
    bool delayedInput_(int);

    int buttonTimes_[6] = {0,0,0,0,0,0};
    int delayms_ = 200;

    Action** buttonActions_;
    JoystickAction* joystickAction_ = nullptr;

    DigitalIn** buttons_;
    int maxButtons_ = 6;
    Joystick* joystick_ = nullptr;
};


#endif