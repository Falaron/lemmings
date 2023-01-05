#pragma once

#include "cocos2d.h"
#include "LemmingAction.h"
#include <vector>

class HUDLayer : public cocos2d::Layer
{
public:

    virtual bool init();

    CREATE_FUNC(HUDLayer);

    void update(float delta) override;

    void InitializeCursorMovementTrigger();
    void CreateActionsHUD();
    void setCursorSprite(const char * sprite);
    void UpdateSelectedActionBorder(int selectedAction);
    
    float GetCursorX() { return cursorX; };
    float GetCursorY() { return cursorY; };

    void ticktock(float dt);

    void updateLemmingsScore();

private:

    cocos2d::SpriteFrameCache* frameCache;
    cocos2d::DrawNode* selectedFrameBorderAction;
    cocos2d::Sprite* cursorSprite;

    std::vector<LemmingAction*> actions;

    cocos2d::Label* comboLabel1;
    cocos2d::Label* timer;
    cocos2d::Label* lemmingsInGameText;
    cocos2d::Label* lemmingsEscapedText;
    float cursorX, cursorY;
    float _seconds, _minutes;

    LemmingActionName cursorOnAction;
    bool isCursorOnAction = false;
};