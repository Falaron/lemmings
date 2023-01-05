#pragma once

#include "cocos2d.h"

class HUDLayer : public cocos2d::Layer
{
public:

    virtual bool init();

    CREATE_FUNC(HUDLayer);

    void InitializeCursorMovementTrigger();
    void CreateActionsHUD();
    void setCursorSprite(const char * sprite);
    void ticktock(float dt);

    void updateLemmingsScore();

private:

    cocos2d::SpriteFrameCache* frameCache;

    cocos2d::Label* comboLabel1;
    cocos2d::Sprite* cursorSprite;
    cocos2d::Label* timer;
    cocos2d::Label* lemmingsInGameText;
    cocos2d::Label* lemmingsEscapedText;
    cocos2d::Label* LemmingvictoryText;
    float cursorX, cursorY;
};