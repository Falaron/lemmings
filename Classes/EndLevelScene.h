#ifndef __ENDLEVEL_SCENE_H__
#define __ENDLEVEL_SCENE_H__

# include "cocos2d.h"
# include "ui/CocosGUI.h"

# include "MainGame.h"
# include "GameManager.h"

class EndLevelScene : public cocos2d::Layer
{
public:
    static cocos2d::Scene* createScene();
    virtual bool init();
    virtual void onEnter();

    // implement the "static create()" method manually
    CREATE_FUNC(EndLevelScene);

    void Quit(Ref* pSender);

private:
};

#endif // __ENDLEVEL_SCENE_H__
