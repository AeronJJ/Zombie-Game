#include "GameScene.h"
#include <cmath>
#include <cstdlib>

GameScene::GameScene(Player* player, Timer* timer, WaveUIEntity* waves, Messenger* messenger, HPUIEntity* hp, PauseMenuEntity* pauseEnt, InputConfig* config, BackButtonEntity* backButt, ExitButtonEntity* exitButt) : 
                    Scene(Coord3D (0,0,0), Coord3D (1,1,1), player, config), time_(timer), wavesEntity_(waves), messenger_(messenger), 
                    hpEntity_(hp), pauseEntity_(pauseEnt), backButton_(backButt), exitButton_(exitButt) /* , config_(player, messenger) */ {
  newZombie_ = nullptr;
  zombieSprites_ = new ZombieSpriteGroup;

  addEntity(wavesEntity_);
  addEntity(hpEntity_);
  addEntity(pauseEntity_);
  addEntity(backButton_);
  addEntity(exitButton_);

  background_ = new Background;
  addEntity(background_);
}

GameScene::~GameScene() {
  delete zombieSprites_;
  delete background_;
}

Scene* GameScene::update() {
  // Check if the wave is cleared:
  if (getRemaining() == 0 && getAlive() == 0) {
    if (!messageSent_) {
      messenger_->Notify(EventMSG::EVENT_WINDOW_CLEAR); // Only send one message, Engine relies on counting how many messages received.
      messageSent_ = true;
    }
  }
  else if (!paused_) {
    spawnLogic_(); // If wave is not cleared, spawn more zombies.
  }
  internalUpdate_(); // This function calls the update function on all entities in the scene, and sorts them
  
  // Next, all entities are checked for scene change flags.
  for (int i = 0; i < getMaxEntities(); i++) {
    Entity* ent = getEntities()[i];
    if (ent != nullptr) {
      int index = ent->goToScene();
      if (validateSceneIndex_(index)) {
        goToSceneFlag_ = index;
      }
      if (!ent->Alive) {
        removeEntity(ent);
        alive_--; // This assumes that the only entity being destroyed is a zombie.. Not great, would need some kind of entity identifier otherwise.
      }
    }
  }
  // If the scene flag is valid, return the relevant scene to the engine
  if (validateSceneIndex_(goToSceneFlag_)) {
    int index = goToSceneFlag_;
    goToSceneFlag_ = -1;
    return getScene(index);
  }
  else {
    return nullptr;
  }
}

void GameScene::nextWave() {
  // Increase the amount of zombies spawning per wave
  wave_++;
  waveStartTimems_ = time_->elapsed_time().count() / 1000;
  messageSent_ = false;
  remaining_ = 3*wave_ + 2;
}

void GameScene::spawnLogic_() {
  // Use timer logic to randomise zombie spawning
  if (time_->elapsed_time().count() / 1000 > waveStartTimems_ + waveDelayms_ && remaining_ > 0 && alive_ < calculateAlive_() && time_->elapsed_time().count() % spawnDelay_ == 0) {
    // Expression is far too long, need to condense.
    if (wavesEntity_ != nullptr) {
      wavesEntity_->move = true;
    }
    // Pseudo-random using timer to vary spawn position, I think it favours certain positions
    double xpos = double(time_->elapsed_time().count()/1000 % 100) / 100;
    if (nextFree_ <= maxEntities_ - 1) {
      // If there is space in the entities list, then spawn a zombie
      newZombie_ = new Zombie(zombieSprites_, int (100*xpos) % 2, messenger_, time_);
      newZombie_->moveEntity(Coord3D (xpos,1,0));
      if (addEntity(newZombie_)) {
        // Randomise the zombies speed, speed increase as wave number increases
        double speedOffset = double(time_->elapsed_time().count()/10000 % 40 + 80) / 100;
        newZombie_->setSpeed((floor(wave_/2)+baseSpeed_)*speedOffset/10000); // This is a lot of math for not a lot of payoff, like it's not even directly noticeable.
        remaining_--;
        alive_++;
      }
      else {
        delete newZombie_; // Delete the zombie if we were unable to add it to the entities list
      }
    }
  }
}

int GameScene::calculateAlive_() { // Does not calculate the number of alive Zombies, it calculates the maximum zombies that can be on screen
  //return 20;
  if (wave_*3 < 15) {
    return wave_*2 + 1;
  }
  else {
    return 15; // Maximum to be displayed on screen.
  }
}

void GameScene::setLeftWindow(Scene* scn) {
  setScene(2, scn);
}

void GameScene::setRightWindow(Scene* scn) {
  setScene(1, scn);
}

int GameScene::getRemaining() {
  return remaining_;
}

int GameScene::getAlive() {
  return alive_;
}

int GameScene::getWave() {
  return wave_;
}

void GameScene::togglePause() {
  paused_ = !paused_;
  //pauseEntity_->update();
  for (int i = 0; i < getMaxEntities(); i++) {
    Entity* ent = getEntities()[i];
    if (ent != nullptr) ent->togglePause(); // This will pause shared entities 4 times, which means no change.
  }
}