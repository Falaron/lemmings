#pragma once

#include "cocos2d.h"

#include "PauseScene.h"
#include "EndLevelScene.h"
#include "GameManager.h"
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
    bool onContactEnter(PhysicsContact& contact);

    // implement the "static create()" method manually
    CREATE_FUNC(MainGame);
    void update(float delta) override;

    //Check if level end
    void checkEndLevel();

    std::vector<Lemmings*> lemmingsList;

private:

    std::vector<cocos2d::EventKeyboard::KeyCode> keys;

    float cursorX, cursorY;

    SpriteFrameCache* frameCache;
    PhysicsShapeCache* physicCache;
    EventListenerPhysicsContact* contactListener;
    GameLayer* gameLayer;
    HUDLayer* hudLayer;
    float cameraMoveTimer;
};