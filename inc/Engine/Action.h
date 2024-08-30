#ifndef ACTION_H
#define ACTION_H

#include "Entity.h"
#include "Joystick.h"

// This class holds a template for actions either the player character or enemies can execute.

class Action {
    public:
    Action(Entity*);
    //Action();
    virtual ~Action();
    virtual void Execute();

    void setEntity(Entity*);

    void setMovementSpeed(double spd);

    protected:
    double movementSpeed_ = 0.005;
    Entity* entity_;

};

class JoystickAction : public Action {
  public:
  JoystickAction(Entity* entity);
  void SetJoystickPos(Vector2D pos);

  protected:
  Vector2D jsPos_;
};

#endif