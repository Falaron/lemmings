#ifndef __PAUSE_SCENE_H__
#define __PAUSE_SCENE_H__

# include "cocos2d.h"
# include "ui/CocosGUI.h"
# include "Definitions.h"

# include "MainGame.h"
# include "MainMenuScene.h"

class PauseMenu : public cocos2d::Layer
{
public:
    static cocos2d::Scene* createScene();
    virtual bool init();
    virtual void onEnter();

    // implement the "static create()" method manually
    CREATE_FUNC(PauseMenu);

    void Return(Ref* pSender);
    void Quit(Ref* pSender);

private:
    cocos2d::Label* standardLabel;
    cocos2d::Label* customTTFLabel;
};

#endif // __PAUSE_SCENE_H__
