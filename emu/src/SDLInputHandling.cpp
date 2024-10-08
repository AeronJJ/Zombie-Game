#include "SDLInputHandling.h"

SDLInputHandling::SDLInputHandling() {
  initialised_ = false;
  if (BUTTONLIST == nullptr) {
    BUTTONLIST = new IOContainer;
  }
  init_();
  //std::cout << "Inputs created\n";
}

void SDLInputHandling::init_() {
  maxInputs_ = BUTTONLIST->getMaxInputs();
  digitals_ = BUTTONLIST->getDigitals();
  analogs_ = BUTTONLIST->getAnalogs();
  fillMap_();
  initialised_ = true;
}

bool SDLInputHandling::checkInputs() {
  //std::cout << "Checking Inputs Start\n";
  //if (!initialised_) init_();
  if (BUTTONLIST->remapRequired()) fillMap_();
  while (SDL_PollEvent(&e_) != 0) {
    if (e_.type == SDL_QUIT) {
      quit_ = true;
      return quit_;
    }
    SDL_Keycode key = e_.key.keysym.sym;
    switch (e_.type) {
    case SDL_KEYDOWN:
      if (keyMap_[key] > 0) {
	//std::cout << "Checking Inputs!\n";
	setButton(keyMap_[key], false);
      }
      if (analogKeyMap_.count(key) > 0) {
	float dir = 1.0;
	if (key == SDLK_UP || key == SDLK_LEFT) dir = 0.0;
	setAnalog(analogKeyMap_[key], dir);
      }
      break;
    case SDL_KEYUP:
      if (keyMap_[key] > 0) {
	setButton(keyMap_[key], true);
      }
      if (analogKeyMap_.count(key) > 0) {
	setAnalog(analogKeyMap_[key], 0.5);
      }
      break;
    default:
      break;
    }
  }
  return quit_;
}

void SDLInputHandling::setButton(int buttonEnumVal, bool pressed) {
  // This is very inefficient, set up second map for positions in button array.
  //std::cout << "Setting Button " << buttonEnumVal << std::endl;
  /*for (int i = 0; i < maxInputs_; i++) {
    if (digitals_[i] != nullptr && digitals_[i]->getPin() == buttonEnumVal) {
      digitals_[i]->set(pressed);
    }
  }*/
  //std::cout << "Set Button start\n";
  //std::cout << buttonEnumVal << std::endl;
  //std::cout << pinToIndex_[buttonEnumVal] << std::endl;
  //std::cout << KB_SPACE << std::endl;
  digitals_[pinToIndex_[buttonEnumVal]]->set(pressed);
  //std::cout << "Set Button end\n";
}

void SDLInputHandling::setAnalog(int analogEnumVal, float val) {
  //std::cout << "Setting Analogs\n";
  for (int i = 0; i < maxInputs_; i++) {
    if (analogs_[i] != nullptr && analogs_[i]->getPin() == analogEnumVal) {
      analogs_[i]->set(val);
    }
  }
}

void SDLInputHandling::fillMap_() {
  //A3 - Shoot
  //PA_11 - Pause
  //PC_13 - 
  //PB_12 - Left
  //PB_11 - Shoot
  //PB_2 - Right
 
  keyMap_[SDLK_SPACE] = KB_SPACE;
  keyMap_[SDLK_ESCAPE] = KB_ESCAPE;
  keyMap_[SDLK_SPACE] = KB_SPACE;
  keyMap_[SDLK_LCTRL] = KB_CTRL;
  keyMap_[SDLK_RETURN] = KB_RETURN;

  keyMap_[SDLK_q] = KB_q;
  keyMap_[SDLK_w] = KB_w;
  keyMap_[SDLK_e] = KB_e;
  keyMap_[SDLK_r] = KB_r;
  keyMap_[SDLK_t] = KB_t;
  keyMap_[SDLK_y] = KB_y;
  keyMap_[SDLK_u] = KB_u;
  keyMap_[SDLK_i] = KB_i;
  keyMap_[SDLK_o] = KB_o;
  keyMap_[SDLK_p] = KB_p;
  keyMap_[SDLK_a] = KB_a;
  keyMap_[SDLK_s] = KB_s;
  keyMap_[SDLK_d] = KB_d;
  keyMap_[SDLK_f] = KB_f;
  keyMap_[SDLK_g] = KB_g;
  keyMap_[SDLK_h] = KB_h;
  keyMap_[SDLK_j] = KB_j;
  keyMap_[SDLK_k] = KB_k;
  keyMap_[SDLK_l] = KB_l;
  keyMap_[SDLK_z] = KB_z;
  keyMap_[SDLK_x] = KB_x;
  keyMap_[SDLK_c] = KB_c;
  keyMap_[SDLK_v] = KB_v;
  keyMap_[SDLK_b] = KB_b;
  keyMap_[SDLK_n] = KB_n;
  keyMap_[SDLK_m] = KB_m;


  analogKeyMap_[SDLK_UP] = PC_0;
  analogKeyMap_[SDLK_DOWN] = PC_0;
  analogKeyMap_[SDLK_LEFT] = PC_1;
  analogKeyMap_[SDLK_RIGHT] = PC_1;

  pinToIndex_.clear();

  for (auto const& x : keyMap_) {
    //std::cout << "First: " << x.first << ", Second: " << x.second << std::endl;
    if (x.second > 0) {
      //std::cout << "Max inputs; " << maxInputs_ << std::endl;
      for (int i = 0; i < maxInputs_; i++) {
	//if (digitals_[i] != nullptr) std::cout << digitals_[i]->getPin() << std::endl;
	if (digitals_[i] != nullptr && digitals_[i]->getPin() == x.second) {
	  pinToIndex_[x.second] = i;
	  //std::cout << i << std::endl;
	}
      }
    }
  }
}
