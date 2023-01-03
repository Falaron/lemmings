# include "EndLevelScene.h"

USING_NS_CC;

using namespace ui;

Scene* EndLevelScene::createScene()
{
    auto scene = Scene::create();
    auto layer = EndLevelScene::create();

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
bool EndLevelScene::init()
{
    if (!Layer::init())
    {
        return false;
    }

    //Important variables setup
    Size screenSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();


    //////////////////////
    // Adding background sprite
    Sprite* backgroundMenu = Sprite::create(MAIN_MENU_BACKGROUND_PATH);
    backgroundMenu->setAnchorPoint(Vec2(0, 0));
    backgroundMenu->setPosition(Vec2(0, 0));
    backgroundMenu->getTexture()->setAliasTexParameters();
    backgroundMenu->setScale(4);
    this->addChild(backgroundMenu, 0);


    // Adding LEVEL REVIEW title
    auto endLevelTitle = Label::createWithSystemFont("LEVEL REVIEW", "fonts/arial.ttf", 40);
    endLevelTitle->setPosition(Vec2(230, 250));
    this->addChild(endLevelTitle);

    // Adding Score
    auto lemmingsEscapedText = Label::createWithSystemFont("Lemmings escaped : " + to_string(GameManager::GetLemmingExit()) + " / " + to_string(GameManager::GetLemmingSpawn()), "fonts/arial.ttf", 20);
    lemmingsEscapedText->setPosition(Vec2(230, 200));
    this->addChild(lemmingsEscapedText);

    auto lemmingsDeadText = Label::createWithSystemFont("Lemmings dead : " + to_string(GameManager::GetLemmingDead()) + " / " + to_string(GameManager::GetLemmingSpawn()), "fonts/arial.ttf", 20);
    lemmingsDeadText->setPosition(Vec2(230, 170));
    this->addChild(lemmingsDeadText);

    if (GameManager::GetLemmingExit == 0)
        winRate = 0;
    else {
        winRate = (float(GameManager::GetLemmingExit()) / GameManager::GetLemmingSpawn()) * 100;
    }
        
    auto winRateText = Label::createWithSystemFont("Win rate : " + to_string(int(winRate)) + "%", "fonts/arial.ttf", 20);
    winRateText->setPosition(Vec2(230, 140));
    this->addChild(winRateText);


    // Quit Menu
    auto menuQuit = MenuItemFont::create("quit", CC_CALLBACK_1(EndLevelScene::Quit, this));
    auto moveTo = MoveBy::create(0, Vec2(0, -50));
    menuQuit->runAction(moveTo);

    auto* menu = Menu::create(menuQuit, NULL);
    menu->setPosition(Point(230, 150));
    this->addChild(menu);


    return true;
}

void EndLevelScene::onEnter()
{
    Layer::onEnter();
    /*auto defaultCamera = Camera::getDefaultCamera();
    auto s = Director::getInstance()->getWinSize();
    defaultCamera->initOrthographic(s.width * 0.66, s.height * 0.66, 1, 2000);
    defaultCamera->setPosition(0, 0);*/

    //changed static zoom to distance between spawn and ecit
}

void EndLevelScene::Quit(cocos2d::Ref* pSender) {
    Director::getInstance()->end();
}