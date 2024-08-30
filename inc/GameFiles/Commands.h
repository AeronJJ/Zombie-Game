#ifndef COMMANDS_H
#define COMMANDS_H

#include "Action.h"
#include "Entity.h"
#include <cmath>
#include "Player.h"
#include "MenuEntities.h"

class moveEntity : public JoystickAction {
  public:
  moveEntity(Entity*);
  void Execute() override;
};

class moveEntityBack : public Action {
  public:
  moveEntityBack(Entity*);
  void Execute() override;
};

class moveEntityForwards : public Action {
  public:
  moveEntityForwards(Entity*);
  void Execute() override;
};

class moveEntityLeft : public Action {
  public:
  moveEntityLeft(Entity*);
  void Execute() override;
};

class moveEntityRight : public Action {
  public:
  moveEntityRight(Entity*);
  void Execute() override;
};

class shootEntity : public Action {
  public:
  shootEntity(Messenger* mssngr, Entity* = nullptr);
  void Execute() override;
  private:
  Messenger* mssngr_;
};

class previousScene : public Action {
  public:
  previousScene(Player*);
  ~previousScene();
  void Execute() override;
  private:
  Player* player_;
};

class rightWindow : public Action {
  public:
  rightWindow(Player*);
  void Execute() override;
  private:
  Player* player_;
};

class leftWindow : public Action {
  public:
  leftWindow(Player*);
  ~leftWindow();
  void Execute() override;
  private:
  Player* player_;
};

class pauseAction : public Action {
  public:
  pauseAction(Messenger* mssngr);
  void Execute() override;
  private:
  Messenger* mssngr_;
};

class backAction : public Action {
  public:
  backAction(Player* player);
  void Execute() override;
  private:
  Player* player_;
};

#endif