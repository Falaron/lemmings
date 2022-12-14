# include "PauseScene.h"

USING_NS_CC;

using namespace ui;

Scene* PauseMenu::createScene()
{
    auto scene = Scene::create();
    auto layer = PauseMenu::create();
    
    scene->addChild(layer);
    return scene;
}

// Print useful error message instead of segfaulting when files are not there.
static void problemLoading(const char* filename)
{
    printf("Error while loading: %s\n", filename);
    printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in MainMenuScene.cpp\n");
}

// Initialize MainMenu instance
bool PauseMenu::init()
{
    if (!Layer::init())
    {
        return false;
    }

    //Important variables setup
    Size screenSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    //auto mainGameScene = HelloWorld::createScene();



    //////////////////////
    // Adding background sprite
    Sprite* backgroundMenu = Sprite::create(MAIN_MENU_BACKGROUND_PATH);
    backgroundMenu->setAnchorPoint(Vec2(0,0));
    backgroundMenu->setPosition(Vec2(0,0));
    backgroundMenu->getTexture()->setAliasTexParameters();
    backgroundMenu->setScale(3);
    this->addChild(backgroundMenu, 0);


    // Adding pause title
    auto pauseTitle = Label::createWithSystemFont("PAUSE", "arial.ttf", 40);
    pauseTitle->setPosition(Vec2(160,250));
    this->addChild(pauseTitle);

    auto menuReturn = MenuItemFont::create("return", CC_CALLBACK_1(PauseMenu::Return,this));
    auto menuQuitMainMenu = MenuItemFont::create("quit", CC_CALLBACK_1(PauseMenu::Quit, this));
    auto moveTo = MoveBy::create(0, Vec2(0, -50));
    menuQuitMainMenu->runAction(moveTo);

    auto* menu = Menu::create(menuReturn, menuQuitMainMenu, NULL);
    menu->setPosition(Point(155, 150));
    this->addChild(menu);

    //Go back to game scene
    auto keyboardListener = EventListenerKeyboard::create();
    keyboardListener->onKeyPressed = [](EventKeyboard::KeyCode keyCode, Event* event) {
        if (keyCode == EventKeyboard::KeyCode::KEY_ESCAPE)
            Director::getInstance()->popScene();
    };

    this->_eventDispatcher->addEventListenerWithSceneGraphPriority(keyboardListener, this);

    return true;
}

void PauseMenu::Return(cocos2d::Ref *pSender) {
    Director::getInstance()->popScene();
}

void PauseMenu::Quit(cocos2d::Ref* pSender) {
    Director::getInstance()->end();
}

void PauseMenu::onEnter()
{
    Layer::onEnter();
    auto defaultCamera = Camera::getDefaultCamera();
    auto s = Director::getInstance()->getWinSize();
    defaultCamera->initOrthographic(s.width * 0.66, s.height * 0.66, 1, 2000);
    defaultCamera->setPosition(0, 0);

    //changed static zoom to distance between spawn and ecit
}

