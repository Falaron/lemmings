#pragma once

#include "cocos2d.h"

class GameLayer : public cocos2d::Layer
{
public:

    virtual bool init();
    CREATE_FUNC(GameLayer);

private:
    cocos2d::Label* comboLabel1;

};