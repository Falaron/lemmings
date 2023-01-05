#pragma once

#include "cocos2d.h"
#include "LemmingAction.h"
#include <vector>

#define HUD_LAYER_NAME "HUDLayer"

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
    void UpdateActionCount();
    
    float GetCursorX() { return cursorX; };
    float GetCursorY() { return cursorY; };

    void ticktock(float dt);

    void updateLemmingsScore();

private:

    cocos2d::SpriteFrameCache* frameCache;
    cocos2d::Sprite* cursorSprite;
    cocos2d::DrawNode* selectedFrameBorderAction;

    std::vector<LemmingAction*> actions;
    LemmingAction* selectedAction;
    int cursorOnActionIndex;
    bool isCursorOnAction = false;

    cocos2d::Label* comboLabel1;
    cocos2d::Label* timer;
    cocos2d::Label* lemmingsInGameText;
    cocos2d::Label* lemmingsEscapedText;
    cocos2d::Label* LemmingvictoryText;

    float cursorX, cursorY;
    float _seconds, _minutes;
};