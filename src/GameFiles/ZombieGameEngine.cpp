#include "ZombieGameEngine.h"
#include <cstdio>
#include <string>

ZombieGameEngine::ZombieGameEngine() : menu_(&player_, &messenger_, &menuInputs_), options_(&player_, &messenger_, &menuInputs_), exitUI_(&uiSprites_, &menuSprites_, &messenger_),
                                       waveUi_(&uiSprites_), hpUI_(&uiSprites_), pauseUI_(&uiSprites_), menuInputs_(&player_, &messenger_), gameInputs_(&player_, &messenger_), backUI_(&uiSprites_, &menuSprites_, &messenger_)
{
  window0_ = new GameScene(&player_, &bootTime_, &waveUi_, &messenger_, &hpUI_, &pauseUI_, &gameInputs_, &backUI_, &exitUI_);
  window1_ = new GameScene(&player_, &bootTime_, &waveUi_, &messenger_, &hpUI_, &pauseUI_, &gameInputs_, &backUI_, &exitUI_);
  window2_ = new GameScene(&player_, &bootTime_, &waveUi_, &messenger_, &hpUI_, &pauseUI_, &gameInputs_, &backUI_, &exitUI_);
  window3_ = new GameScene(&player_, &bootTime_, &waveUi_, &messenger_, &hpUI_, &pauseUI_, &gameInputs_, &backUI_, &exitUI_);

  customInit_();
}

ZombieGameEngine::~ZombieGameEngine() {
  delete window0_;
  delete window1_;
  delete window2_;
  delete window3_;
}

void ZombieGameEngine::customInit_() {
    player_.updateScene(&menu_);

    inputHandler_.changeConfig(menu_.getInputConfig()->getActions(), menu_.getInputConfig()->getJSAction());

    window0_->setLeftWindow(window3_);
    window0_->setRightWindow(window1_);

    window1_->setLeftWindow(window0_);
    window1_->setRightWindow(window2_);

    window2_->setLeftWindow(window1_);
    window2_->setRightWindow(window3_);

    window3_->setLeftWindow(window2_);
    window3_->setRightWindow(window0_);

    menu_.setScene(1, &options_);
    menu_.setScene(2, window0_);

    options_.setScene(0, &menu_);
    options_.setScene(2, &menu_); // Temporary. // lol

    renderer_.updateScene(&menu_);
}

void ZombieGameEngine::customLoopLogic_() {
  handleMessages_(); // Maximum of 10 messages per tick, can be increased in Messenger.h

  if (remap_ != nullptr && currentScene_ == &menu_) {
    endRemap_(false);
  }

  if (currentScene_ == window0_ || currentScene_ == window1_ || currentScene_ == window2_ || currentScene_ == window3_) { // Need to update all windows, but don't want to double update the active one.
    if (bootTime_.elapsed_time().count() > dayCounter + 60000000) {
      dayCounter = bootTime_.elapsed_time().count();
      invertLCD_();
    }
    if (currentScene_ != window0_) {
      window0_->update();
    }
    if (currentScene_ != window1_) {
      window1_->update();
    }
    if (currentScene_ != window2_) {
      window2_->update();
    }
    if (currentScene_ != window3_) {
      window3_->update();
    }
  }

  if (windowsCleared_ >= windowsActive_){
    windowsCleared_ = 0;
    window0_->nextWave();
    window1_->nextWave();
    window2_->nextWave();
    window3_->nextWave();
    currentWave_++;
    waveUi_.setWave(currentWave_);
  }

  if (newScene_ != renderer_.getScene() && newScene_ != nullptr) {
    changeScene_(newScene_);
  }

}

void ZombieGameEngine::handleMessages_() {
  EventMSG nxtMsg = messenger_.readNextMessage();
  while(nxtMsg != EventMSG::EVENT_DEFAULT) {
    switch (nxtMsg) {
      case EventMSG::EVENT_DEFAULT:
        break;
      case EventMSG::EVENT_TOGGLE_DBG:
        ToggleDBGMem();
        break;
      case EventMSG::EVENT_TOGGLE_FPS:
        ToggleFPSCounter();
        break; 
      case EventMSG::EVENT_WINDOW_CLEAR:
        windowsCleared_++;
        break;
      case EventMSG::EVENT_ZOMBIE_KILLED:
        score_++;
        break;
      case EventMSG::EVENT_NO_HEALTH:
        gameOver_();
        break;
      case EventMSG::EVENT_GUN_SHOT:
        if (renderer_.getScene()->getFocused() != nullptr) renderer_.getScene()->getFocused()->shot();
        break;
      case EventMSG::EVENT_PAUSE_GAME:
        pause_();
        break;
      case EventMSG::EVENT_PLAYER_HIT:
        if (hpUI_.removeHealth()) {
          messenger_.Notify(EventMSG::EVENT_NO_HEALTH);
        }
        break;
      case EventMSG::EVENT_QUIT:
        if (gameOverScene_ != nullptr) {
          delete gameOverScene_;
          gameOverScene_ = nullptr;
        }
        pause_();
        resetGameScenes_();
        changeScene_(&menu_);
        break;
      case EventMSG::EVENT_CLEAR_SCORE:
        score_ = 0;
        break;
      case EventMSG::EVENT_REMAP_BUTTONS:
        remapSequence_();
        break;
      case EventMSG::EVENT_REMAP_COMPLETED:
        endRemap_();
        break;
    }
    nxtMsg = messenger_.readNextMessage();
  }
}

void ZombieGameEngine::gameOver_() {
  pause_();
  gameOverScene_ = new GameOverScene(&player_, &messenger_, &menuInputs_, &uiSprites_, &menuSprites_, score_);
  changeScene_(gameOverScene_);
}

void ZombieGameEngine::pause_() {
  pauseUI_.togglePause(); // <-- This should not be necessary, but need it to offset the 4 toggles below.
  backUI_.togglePause();
  exitUI_.togglePause(); // I really need to fix this lol
  window0_->togglePause();
  window1_->togglePause();
  window2_->togglePause();
  window3_->togglePause();
}

void ZombieGameEngine::changeScene_(Scene* newScene) {
  player_.updateScene(newScene);
  renderer_.updateScene(newScene);
  if (newScene->getInputConfig() != nullptr) { // If controller config is not defined, do not change config. Should not be required by release.
    inputHandler_.changeConfig(newScene->getInputConfig()->getActions(), newScene->getInputConfig()->getJSAction());
  }
}

void ZombieGameEngine::resetGameScenes_() {
  messenger_.Notify(EventMSG::EVENT_CLEAR_SCORE);
  delete window0_;
  delete window1_;
  delete window2_;
  delete window3_;
  waveUi_.setWave(1);
  hpUI_.heal(60);
  windowsCleared_ = 0;
  currentWave_ = 0;

  window0_ = new GameScene(&player_, &bootTime_, &waveUi_, &messenger_, &hpUI_, &pauseUI_, &gameInputs_, &backUI_, &exitUI_);
  window1_ = new GameScene(&player_, &bootTime_, &waveUi_, &messenger_, &hpUI_, &pauseUI_, &gameInputs_, &backUI_, &exitUI_);
  window2_ = new GameScene(&player_, &bootTime_, &waveUi_, &messenger_, &hpUI_, &pauseUI_, &gameInputs_, &backUI_, &exitUI_);
  window3_ = new GameScene(&player_, &bootTime_, &waveUi_, &messenger_, &hpUI_, &pauseUI_, &gameInputs_, &backUI_, &exitUI_);

  window0_->setLeftWindow(window3_);
  window0_->setRightWindow(window1_);

  window1_->setLeftWindow(window0_);
  window1_->setRightWindow(window2_);

  window2_->setLeftWindow(window1_);
  window2_->setRightWindow(window3_);

  window3_->setLeftWindow(window2_);
  window3_->setRightWindow(window0_);

  menu_.setScene(2, window0_);
}

void ZombieGameEngine::remapSequence_() {
  remapSprites_ = new RemapSpriteGroup;
  remap_ = new RemapButtonScene(remapSprites_, &player_, &menuInputs_, &messenger_);
  remap_->setScene(0, &menu_);
  changeScene_(remap_);
}

void ZombieGameEngine::endRemap_(bool apply) {
  if (apply) {
    int button = -1;
    switch (remap_->buttonToMap) {
      case ButtonMSG::BUTTON_0:
        break;
      case ButtonMSG::BUTTON_1:
        button = 2;
        break;
      case ButtonMSG::BUTTON_2:
        button = 3;
        break;
      case ButtonMSG::BUTTON_3:
        button = 4;
        break;
      case ButtonMSG::BUTTON_4:
        button = 5;
        break;
      case ButtonMSG::BUTTON_5:
        button = 0;
        break;
      case ButtonMSG::BUTTON_NULL:
        break;
      case ButtonMSG::BUTTON_DEFAULTS:
        gameInputs_.resetInputs();
        break;
    }

    if (button != -1) {
      switch (remap_->commandToMap) {
        case CommandMSG::COMMAND_NULL:
          break;
        case CommandMSG::COMMAND_GO_LEFT:
          gameInputs_.mapLeft(button);
          break;
        case CommandMSG::COMMAND_GO_RIGHT:
          gameInputs_.mapRight(button);
          break;
        case CommandMSG::COMMAND_PAUSE:
          gameInputs_.mapPause(button);
          break;
        case CommandMSG::COMMAND_SHOOT:
          gameInputs_.mapShoot(button);
          break;
      }
    }
  }

  delete remapSprites_;
  delete remap_;
  remapSprites_ = nullptr;
  remap_ = nullptr;
}

