#ifndef MESSENGER_H
#define MESSENGER_H

#include "mbed.h"


enum class EventMSG {
  EVENT_DEFAULT,
  EVENT_TOGGLE_FPS,
  EVENT_TOGGLE_DBG,
  EVENT_WINDOW_CLEAR,
  EVENT_ZOMBIE_KILLED,
  EVENT_NO_HEALTH,
  EVENT_GUN_SHOT,
  EVENT_PAUSE_GAME,
  EVENT_PLAYER_HIT,
  EVENT_QUIT,
  EVENT_CLEAR_SCORE,
  EVENT_REMAP_BUTTONS,
  EVENT_REMAP_COMPLETED
};

class Messenger {
  public:
  Messenger();
  ~Messenger();
  void Notify(EventMSG);
  EventMSG readNextMessage();
  private:
  void clearMessages_();
  const static int maxMessages_ = 10;
  int nextFree_ = 0;
  EventMSG messages_[maxMessages_];

};

#endif