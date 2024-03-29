#pragma once

#include "cocos2d.h"

#include <iostream>
#include <vector>
#include <CCScheduler.h>

#include "GameManager.h"
#include "EndLevelScene.h"
#include "PauseScene.h"
#include "Layers/HUDLayer.h"
#include "Layers/GameLayer.h"

using namespace std;

class MainGame : public cocos2d::Scene
{
public:

    static cocos2d::Scene* createScene();

    bool init() override;

    void onEnterTransitionDidFinish() override;
    bool onContactEnter(PhysicsContact& contact);
    bool onContactExit(PhysicsContact& contact);

    void InitCamera();

    // implement the "static create()" method manually
    CREATE_FUNC(MainGame);
    void update(float delta) override;


    void timer(float dt);

    std::vector<Lemmings*> lemmingsList;

private:

    Size windowSize;

    SpriteFrameCache* frameCache;
    PhysicsShapeCache* physicCache;
    EventListenerPhysicsContact* contactListener;
    EventListenerMouse* mouseListener;
    bool mouseDown;

    GameLayer* gameLayer;
    HUDLayer* hudLayer;
    Lemmings* selectedLemmings;
};