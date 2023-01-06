# include "EndLevelScene.h"
# include "Layers/GameLayer.h"
# include "LevelRegistry.h"

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
    isNextLEvel = false;

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
    endLevelTitle->setPosition(Vec2(240, 290));
    this->addChild(endLevelTitle);

    // Adding Score
    auto lemmingsEscapedText = Label::createWithSystemFont("Lemmings escaped : " + to_string(GameManager::GetLemmingExit()) + " / " + to_string(GameManager::GetLemmingSpawn()), "fonts/arial.ttf", 20);
    lemmingsEscapedText->setAnchorPoint(Vec2(0.f, 0.f));
    lemmingsEscapedText->setPosition(Vec2(80, 220));
    this->addChild(lemmingsEscapedText);

    auto lemmingsDeadText = Label::createWithSystemFont("Lemmings dead : " + to_string(GameManager::GetLemmingDead()) + " / " + to_string(GameManager::GetLemmingSpawn()), "fonts/arial.ttf", 20);
    lemmingsDeadText->setAnchorPoint(Vec2(0.f, 0.f));
    lemmingsDeadText->setPosition(Vec2(80, 190));
    this->addChild(lemmingsDeadText);


    auto timerText = Label::createWithSystemFont("Time remaining : " + std::to_string(GameManager::getMinutes()) + " - " + std::to_string(GameManager::getSeconds()), "fonts / arial.ttf", 20);
    timerText->setAnchorPoint(Vec2(0.f, 0.f));
    timerText->setPosition(Vec2(80, 160));
    this->addChild(timerText);

    if (GameManager::GetLemmingExit == 0)
        winRate = 0;
    else {
        winRate = (float(GameManager::GetLemmingExit()) / GameManager::GetLemmingSpawn()) * 100;
    }

    auto winRateText = Label::createWithSystemFont("Win rate : " + to_string(int(winRate)) + "%   of   " + to_string(int(float(GameManager::GetLemmingVictory()) / GameManager::GetLemmingSpawn() * 100)) + "%", "fonts/arial.ttf", 20);
    winRateText->setAnchorPoint(Vec2(0.f, 0.f));
    winRateText->setPosition(Vec2(80, 130));
    this->addChild(winRateText);

    auto victoryConditionText = Label::createWithSystemFont("FAILED", "fonts / arial.ttf", 40);
    victoryConditionText->setAnchorPoint(Vec2(0.f, 0.f));
    victoryConditionText->setPosition(Vec2(80, 80));
    this->addChild(victoryConditionText);
    if (winRate >= int(float(GameManager::GetLemmingVictory()) / GameManager::GetLemmingSpawn() * 100)) {
        victoryConditionText->setString("VICTORY");
    }


    // Quit Menu
    auto menuQuit = MenuItemFont::create("quit", CC_CALLBACK_1(EndLevelScene::Quit, this));
    auto moveTo = MoveBy::create(0, Vec2(0, -50));
    menuQuit->setFontSizeObj(20);
    menuQuit->runAction(moveTo);

    auto menu = Menu::create(menuQuit, NULL);
    menu->setPosition(Point(230, 90));
    this->addChild(menu);

    if (GameManager::GetCurrentLevel()+1 <= LevelRegistry::GetTotalLevels())
    {
        auto nextLevelButton = Button::create();
        nextLevelButton->setTitleText("Next Level");
        nextLevelButton->setPosition(Vec2(300, 90));
        nextLevelButton->addTouchEventListener([&](Ref* sender, Widget::TouchEventType type) {
            if (type == ui::Widget::TouchEventType::ENDED)
                if (!isNextLEvel)
                {
                    GameManager::Reset();
                    GameManager::IncreaseLevel();
                    Director::getInstance()->replaceScene(MainGame::createScene());
                    isNextLEvel = true;
                }
            });
        this->addChild(nextLevelButton);
    }

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