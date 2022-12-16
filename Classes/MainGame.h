#pragma once

#include "cocos2d.h"

#include "PauseScene.h"

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


private:

    std::vector<cocos2d::EventKeyboard::KeyCode> keys;

    EventListenerPhysicsContact* contactListener;
    GameLayer* gameLayer;
    HUDLayer* hudLayer;
    float cameraMoveTimer;
};