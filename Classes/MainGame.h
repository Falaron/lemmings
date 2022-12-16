#pragma once

#include "cocos2d.h"

#include "PauseScene.h"
#include <iostream>
using namespace std;

#include "Layers/HUDLayer.h"
#include "Layers/GameLayer.h"

class MainGame : public cocos2d::Scene
{
public:

    static cocos2d::Scene* createScene();

    bool init() override;
    bool isKeyPressed(cocos2d::EventKeyboard::KeyCode);

    void onEnterTransitionDidFinish() override;

    void InitCamera();
    void InitSpawnAndExit();
    bool onContactEnter(PhysicsContact& contact);

    // implement the "static create()" method manually
    CREATE_FUNC(MainGame);
    void update(float delta) override;


private:

    std::vector<cocos2d::EventKeyboard::KeyCode> keys;

    GameLayer* gameLayer;
    HUDLayer* hudLayer;
    float cameraMoveTimer;
};