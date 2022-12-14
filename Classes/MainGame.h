#pragma once

#include "cocos2d.h"
#include "MapLoader.h"
#include <vector>
#include "Lemmings.h"
#include "PhysicsShapeCache.h"

#include "PauseScene.h"

class MainGame : public cocos2d::Layer
{
public:
    static cocos2d::Scene* createScene();

    bool init() override;
    void onEnter() override;
    bool isKeyPressed(cocos2d::EventKeyboard::KeyCode);

    // a selector callback
    void menuCloseCallback(cocos2d::Ref* pSender);

    void InitCamera();
    void InitSpawnAndExit();

    // implement the "static create()" method manually
    CREATE_FUNC(MainGame);
    void update(float delta) override;

    std::vector<Lemmings*> lemmingsList;

private:
    std::vector<cocos2d::EventKeyboard::KeyCode> keys;

    cocos2d::Sprite* cursorSprite;
    cocos2d::Sprite* _exit;
    cocos2d::Sprite* _spawn;
    float cursorX, cursorY;

    SpriteFrameCache* frameCache;
    PhysicsShapeCache* physicCache;
};