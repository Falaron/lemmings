#pragma once

#include "cocos2d.h"

class MainGame : public cocos2d::Scene
{
public:
    static cocos2d::Scene* createScene();

    bool init() override;

    // a selector callback
    void menuCloseCallback(cocos2d::Ref* pSender);

    // implement the "static create()" method manually
    CREATE_FUNC(MainGame);

private:

    cocos2d::TMXTiledMap* _tileMap;
    cocos2d::TMXLayer* _backGround;
    cocos2d::TMXObjectGroup* _collision;
    cocos2d::TMXObjectGroup* _spawnPoint;
};
