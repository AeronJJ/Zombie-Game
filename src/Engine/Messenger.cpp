#include "Messenger.h"

Messenger::Messenger() {
  clearMessages_();
}

Messenger::~Messenger() {}

void Messenger::Notify(EventMSG msg) {
  if(nextFree_<maxMessages_){
    messages_[nextFree_] = msg;
    nextFree_++;
  }
}

EventMSG Messenger::readNextMessage() {
  if (nextFree_ > 0) {
    nextFree_--;
    EventMSG msg = messages_[nextFree_];
    messages_[nextFree_] = EventMSG::EVENT_DEFAULT;
    return msg;
  }
  else return EventMSG::EVENT_DEFAULT;
}

void Messenger::clearMessages_() {
  for (int i = 0; i < maxMessages_; i++) {
    messages_[i] = EventMSG::EVENT_DEFAULT;
  }
}