#ifndef __MAINMENU_SCENE_H__
#define __MAINMENU_SCENE_H__

# include "cocos2d.h"
# include "ui/CocosGUI.h"
# include "Definitions.h"

class MainMenu : public cocos2d::Scene
{
public:
    static cocos2d::Scene* createScene();
    virtual bool init();

    // implement the "static create()" method manually
    CREATE_FUNC(MainMenu);
private:
    
};

#endif // __MAINMENU_SCENE_H__
