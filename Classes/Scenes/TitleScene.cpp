# include "TitleScene.h"

USING_NS_CC;

using namespace ui;

Scene* MainMenu::createScene()
{
    auto scene = Scene::create();
    auto layer = MainMenu::create();
    
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
bool MainMenu::init()
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


    // Adding title sprite
    Sprite* titleMenu = Sprite::create(MAIN_MENU_TITLE_PATH);
    titleMenu->setPosition(Vec2(160, 220));
    titleMenu->getTexture()->setAliasTexParameters();
    titleMenu->setScale(1.7f);
    this->addChild(titleMenu, 1);

    // Create sequences of titleMenu sprite
    auto moveBy = MoveBy::create(2.0f, Vec2(0.0f, -titleMenu->getContentSize().height));
    auto moveBounceOut = EaseBounceOut::create(moveBy->clone());

    auto rotate = RotateTo::create(4.0f, -2.0f);
    auto rotateReverse = RotateTo::create(4.0f, 2.0f);
    auto scale = ScaleTo::create(2.0f, 1.7f);
    auto scaleReverse = ScaleTo::create(2.0f, 1.65f);

    auto rotateSequence = Sequence::create(rotate, rotateReverse, nullptr);
    auto scaleSequence = Sequence::create(scale, scaleReverse, nullptr);

    titleMenu->runAction(moveBounceOut);
    titleMenu->runAction(RepeatForever::create(rotateSequence));
    titleMenu->runAction(RepeatForever::create(scaleSequence));


    // Adding Play button
    auto button = Button::create(MAIN_MENU_BUTTON_PLAY_NORMAL);
    button->setScale(.5f);
    button->setPosition(Vec2(95, 75));

    button->addTouchEventListener([&](Ref* sender, Widget::TouchEventType type) {
        if (type == ui::Widget::TouchEventType::ENDED)
            Director::getInstance()->replaceScene(MainGame::createScene());
    });

    this->addChild(button);

    // Adding Quit button
    auto button2 = Button::create(MAIN_MENU_BUTTON_QUIT_NORMAL);
    button2->setScale(.5f);
    button2->setPosition(Vec2(220, 75));
    button2->addTouchEventListener([&](Ref* sender, Widget::TouchEventType type){
        if(type == ui::Widget::TouchEventType::ENDED)
            Director::getInstance()->end();
        });
    this->addChild(button2);

    // Adding credits
    auto credit = Label::createWithSystemFont("Albert & Co. 2022 - All right reserved", "arial.ttf", 6);
    credit->setPosition(Vec2(160,10));
    this->addChild(credit);

    return true;
}

void MainMenu::onEnter()
{
    Layer::onEnter();
    auto defaultCamera = Camera::getDefaultCamera();
    auto s = Director::getInstance()->getWinSize();
    defaultCamera->initOrthographic(s.width * 0.66, s.height * 0.66, 1, 2000);
    defaultCamera->setPosition(0, 0);

    //changed static zoom to distance between spawn and ecit
}

