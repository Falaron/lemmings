# include "MainMenuScene.h"

USING_NS_CC;

using namespace ui;

Scene* MainMenu::createScene()
{
    auto scene = Scene::create();
    auto layer = Layer::create();
    
    scene->addChild(layer);
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



    //////////////////////
    // Adding background sprite
    Sprite* backgroundMenu = Sprite::create(MAIN_MENU_BACKGROUND_PATH);
    backgroundMenu->setPosition(Vec2(origin.x + screenSize.width/2, origin.y + screenSize.height/2));
    backgroundMenu->getTexture()->setAliasTexParameters();
    this->addChild(backgroundMenu, 0);


    // Adding title sprite
    Sprite* titleMenu = Sprite::create(MAIN_MENU_TITLE_PATH);
    titleMenu->setPosition(Vec2(origin.x + screenSize.width * .5f, screenSize.height + titleMenu->getContentSize().height - 70));
    titleMenu->getTexture()->setAliasTexParameters();
    titleMenu->setScale(.5);
    this->addChild(titleMenu, 1);

    // Create sequences of titleMenu sprite
    auto moveBy = MoveBy::create(2.0f, Vec2(0.0f, -titleMenu->getContentSize().height));
    auto moveBounceOut = EaseBounceOut::create(moveBy->clone());

    auto rotate = RotateTo::create(4.0f, -2.0f);
    auto rotateReverse = RotateTo::create(4.0f, 2.0f);
    auto scale = ScaleTo::create(2.0f, 0.5f);
    auto scaleReverse = ScaleTo::create(2.0f, 0.47f);

    auto rotateSequence = Sequence::create(rotate, rotateReverse, nullptr);
    auto scaleSequence = Sequence::create(scale, scaleReverse, nullptr);

    titleMenu->runAction(moveBounceOut);
    titleMenu->runAction(RepeatForever::create(rotateSequence));
    titleMenu->runAction(RepeatForever::create(scaleSequence));


    // Adding Play button
    auto button = Button::create(MAIN_MENU_BUTTON_PLAY_NORMAL, MAIN_MENU_BUTTON_PLAY_SELECTED);
    //button->getRendererNormal()->setAliasTexParameters();
    button->setScale(.2f);
    button->setPosition(Vec2(origin.x + screenSize.width * 0.25f, origin.y + screenSize.height * 0.3f));

    button->addTouchEventListener([&](Ref* sender, Widget::TouchEventType type) {
        switch (type)
        {
        case ui::Widget::TouchEventType::BEGAN:
            break;
        case ui::Widget::TouchEventType::ENDED:
            /*std::cout << "Button 1 clicked" << std::endl;*/
            break;
        default:
            break;
        }
        });

    this->addChild(button);

    auto button2 = Button::create(MAIN_MENU_BUTTON_PLAY_NORMAL, MAIN_MENU_BUTTON_PLAY_SELECTED);
    //button->getRendererNormal()->setAliasTexParameters();
    button2->setScale(.2f);
    button2->setPosition(Vec2(origin.x + screenSize.width * 0.75f, origin.y + screenSize.height * 0.3f));

    button2->addTouchEventListener([&](Ref* sender, Widget::TouchEventType type) {
        switch (type)
        {
        case ui::Widget::TouchEventType::BEGAN:
            break;
        case ui::Widget::TouchEventType::ENDED:
            /*std::cout << "Button 1 clicked" << std::endl;*/
            break;
        default:
            break;
        }
        });

    this->addChild(button2);

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

