#pragma once

#include "cocos2d.h"
#include "Lemmings.h"

#include "PhysicsShapeCache.h"

#define GAME_LAYER_NAME "GameLayer"

class GameLayer : public cocos2d::Layer
{
public:

    bool init() override;
    CREATE_FUNC(GameLayer);
    void update(float delta) override;

    void InitSpawnAndExit();
    void SpawnLemmings();
    void RemoveLemming(Lemmings*);

    Vec2 GetExitPos() { return _exit->getPosition(); }
    Vec2 GetSpawnPos() { return _spawn->getPosition(); }
    Size GetExitSize() { return _exit->getContentSize(); }
    Size GetSpawnSize() { return _spawn->getContentSize(); }

private:


    std::vector<Lemmings*> lemmingsList;

    cocos2d::Sprite* _exit;
    cocos2d::Sprite* _spawn;

    SpriteFrameCache* frameCache;
    PhysicsShapeCache* physicCache;

};