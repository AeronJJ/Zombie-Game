#include "Action.h"

Action::Action(Entity* entity) : entity_(entity) {};

Action::~Action() {};

void Action::Execute() {}



void Action::setMovementSpeed(double spd) {
  movementSpeed_ = spd;
}

void Action::setEntity(Entity* ent) {
  entity_ = ent;
} 

JoystickAction::JoystickAction(Entity* entity) : Action(entity) {}

void JoystickAction::SetJoystickPos(Vector2D pos) {
  jsPos_ = pos;
}