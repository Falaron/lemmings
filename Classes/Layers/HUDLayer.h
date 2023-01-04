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

private:

    cocos2d::SpriteFrameCache* frameCache;
    cocos2d::DrawNode* selectedFrameBorderAction;
    cocos2d::Sprite* cursorSprite;

    std::vector<LemmingAction*> actions;

    float cursorX, cursorY;
    float timer;

    int cursorOnAction;
};