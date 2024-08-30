#ifndef ZOMBIEGAMEENGINE_H
#define ZOMBIEGAMEENGINE_H

#include "Engine.h"

#include "Zombie.h"
#include "Player.h"
#include "Background.h"
#include "MenuEntities.h"
#include "UIEntities.h"

#include "GameScene.h"
#include "MenuScene.h"

#include "Commands.h"

#include "Messenger.h"

#include "GameOverScene.h"
#include "RemapScene.h"


class ZombieGameEngine : public Engine {
    public:
    ZombieGameEngine();
    ~ZombieGameEngine();

    private:
    void customLoopLogic_() override;
    void customInit_() override; // This can't be called in base constructor
    void gameOver_();
    void pause_();

    void handleMessages_();

    void changeScene_(Scene* newScene);
    void resetGameScenes_();

    void remapSequence_();
    void endRemap_(bool apply = true);
    void mapButton_();

    Messenger messenger_;
    int windowsCleared_ = 0;
    int windowsActive_ = 4;

    // Sprite Groups:
    UISpriteGroup uiSprites_;
    MenuSpriteGroup menuSprites_;
    RemapSpriteGroup* remapSprites_;

    // Entities:
    Player player_;
    WaveUIEntity waveUi_;
    HPUIEntity hpUI_;
    PauseMenuEntity pauseUI_;
    BackButtonEntity backUI_;
    ExitButtonEntity exitUI_;

    // Scenes:
    MainMenuScene menu_;
    OptionsMenuScene options_;
    GameScene* window0_;
    GameScene* window1_;
    GameScene* window2_;
    GameScene* window3_;
    GameOverScene* gameOverScene_ = nullptr;

    RemapButtonScene* remap_ = nullptr;

    // Configs:
    MenuInputConfig menuInputs_;
    GameInputConfig gameInputs_;

    int currentWave_ = 0;
    int score_ = 0;

    int dayCounter = 0;
    
};

#endif