#ifndef REMAPSCENE_H
#define REMAPSCENE_H

#include "Scene.h"
#include "RemapEntities.h"
#include "Player.h"

class RemapCommandScene : public Scene {
  public:
  RemapCommandScene(RemapSpriteGroup* sprGrp, Player* player, InputConfig* config);
  ~RemapCommandScene();
  Scene* update() override;
  CommandMSG commandToMap = CommandMSG::COMMAND_NULL;
  private:
  RemapSpriteGroup* sprGrp_;
  ShootButtonEntity* shootButt_;
  GoLeftButtonEntity* leftButt_;
  GoRightButtonEntity* rightButt_;
  PauseButtonEntity* pauseButt_;
};

class RemapButtonScene : public Scene {
  public:
  RemapButtonScene(RemapSpriteGroup* sprGrp, Player* player, InputConfig* config, Messenger* mssngr);
  ~RemapButtonScene();
  Scene* update() override;
  ButtonMSG buttonToMap = ButtonMSG::BUTTON_NULL;
  CommandMSG commandToMap = CommandMSG::COMMAND_NULL;
  private:
  void goToCommandScene_();
  void destroyCommandScene_();
  RemapCommandScene* commandScene_ = nullptr;
  RemapSpriteGroup* sprGrp_;
  LoadDefaultsEntity* defaults_;
  Button1Entity* butt1_;
  Button2Entity* butt2_;
  Button3Entity* butt3_;
  Button4Entity* butt4_;
  Button5Entity* butt5_;
  DiagramEntity* diag_;
  Player* player_;
  Messenger* mssngr_;


};

#endif