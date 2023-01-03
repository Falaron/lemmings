#pragma once

#include "cocos2d.h"

class HUDLayer : public cocos2d::Layer
{
public:

    virtual bool init();
    CREATE_FUNC(HUDLayer);
    void InitializeCursorMovementTrigger();
    void CreateActionsHUD();

private:

    cocos2d::SpriteFrameCache* frameCache;

    cocos2d::Label* comboLabel1;
    cocos2d::Sprite* cursorSprite;
    float cursorX, cursorY;
    float timer;
};