#ifndef CONFIGS_H
#define CONFIGS_H

#include "InputConfig.h"
#include "Commands.h"

class MenuInputConfig : public InputConfig {
  public:
  MenuInputConfig(Player* player, Messenger* mssngr);
  ~MenuInputConfig();
  private:
  moveEntity js_;
  shootEntity shoot_;
  backAction back_;

  Messenger* mssngr_;

};

class GameInputConfig : public InputConfig {
  public:
  GameInputConfig(Player* player, Messenger* mssngr);
  void resetInputs();
  void mapPause(int i);
  void mapShoot(int i);
  void mapLeft(int i);
  void mapRight(int i);

  private:
  moveEntity js_;
  shootEntity shoot_;
  leftWindow left_;
  rightWindow right_;
  pauseAction pause_;


  Messenger* mssngr_;
};

#endif