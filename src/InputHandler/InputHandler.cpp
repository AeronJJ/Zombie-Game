#include "InputHandler.h"

InputHandler::InputHandler(Timer* timer, Joystick* joystick, DigitalIn* button0, DigitalIn* button1, DigitalIn* button2, DigitalIn* button3, DigitalIn* button4, DigitalIn* button5, Action** defaultConfig) 
: delayTimer(timer), joystick_(joystick) {

  buttons_ = new DigitalIn*[maxButtons_];

  buttons_[0] = button0;
  buttons_[1] = button1;
  buttons_[2] = button2;
  buttons_[3] = button3;
  buttons_[4] = button4;
  buttons_[5] = button5;

  buttonActions_ = defaultConfig;

}

InputHandler::~InputHandler() {
  delete [] buttons_;
}

void InputHandler::HandleInputs() {
  if (joystick_ != nullptr && joystickAction_ != nullptr) {
    Vector2D joyDir = joystick_->get_mapped_coord();
    if (joyDir.x > 0.05 || joyDir.y > 0.05 || joyDir.x < -0.05 || joyDir.y < -0.05) { 
      joystickAction_->SetJoystickPos(joyDir);
      joystickAction_->Execute();
    }
  }

  for (int i = 0; i < maxButtons_; i++) {
    if (buttons_[i] != nullptr && buttonActions_[i] != nullptr) {
      if (!buttons_[i]->read() && delayedInput_(i)) {
        buttonTimes_[i] = delayTimer->elapsed_time().count() / 1000;
        buttonActions_[i]->Execute();
      }
    }
  }
}


void InputHandler::bindButton(Action* butt, int num) { 
  if (num < maxButtons_ && num >= 0) {
    buttonActions_[num] = butt;
  }
}

void InputHandler::bindJoystick(JoystickAction* js) {joystickAction_ = js;}

bool InputHandler::delayedInput_(int button) {
  if (delayTimer->elapsed_time().count() / 1000 > buttonTimes_[button] + delayms_) {
    return true;
  }
  else {
    return false;
  }
}

void InputHandler::changeConfig(Action** newConfig, JoystickAction* jsConf) {
  buttonActions_ = newConfig;
  joystickAction_ = jsConf;
}