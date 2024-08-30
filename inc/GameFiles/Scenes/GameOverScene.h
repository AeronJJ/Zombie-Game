#ifndef GAMEOVERSCENE_H
#define GAMEOVERSCENE_H

#include "Scene.h"
#include "UIEntities.h"
#include "Player.h"
#include "Background.h"

class GameOverScene : public Scene {
  public:
    GameOverScene(Player* player, Messenger* mssngr, InputConfig* config, UISpriteGroup* uiSprites, MenuSpriteGroup* menuSprites, int score);
    ~GameOverScene();
  private:
    UISpriteGroup* uiSprites_;
    MenuSpriteGroup* menuSprites_;

    int scoreVal_;

    ExitButtonEntity* exit_;
    GameOverEntity* gameOver_;
    ScoreEntity* score_;
    Background* background_;

    Messenger* mssngr_;
};

#endif