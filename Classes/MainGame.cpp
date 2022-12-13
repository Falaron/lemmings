#include "MainGame.h"

USING_NS_CC;

Scene* MainGame::createScene()
{
    auto scene = Scene::createWithPhysics();
    scene->getPhysicsWorld()->setDebugDrawMask(cocos2d::PhysicsWorld::DEBUGDRAW_ALL);

    auto layer = MainGame::create();
    scene->addChild(layer);

    return scene;
}

// Print useful error message instead of segfaulting when files are not there.
static void problemLoading(const char* filename)
{
    printf("Error while loading: %s\n", filename);
    printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in HelloWorldScene.cpp\n");
}

// on "init" you need to initialize your instance
bool MainGame::init()
{
    if (!Scene::initWithPhysics()) return false;

    MapLoader::LoadMap("maps/test.tmx", this);

    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    auto closeItem = MenuItemImage::create(
        "CloseNormal.png",
        "CloseSelected.png",
        CC_CALLBACK_1(MainGame::menuCloseCallback, this));

    if (closeItem == nullptr ||
        closeItem->getContentSize().width <= 0 ||
        closeItem->getContentSize().height <= 0)
    {
        problemLoading("'CloseNormal.png' and 'CloseSelected.png'");
    }
    else
    {
        float x = origin.x + visibleSize.width - closeItem->getContentSize().width / 2;
        float y = origin.y + closeItem->getContentSize().height / 2;
        closeItem->setPosition(Vec2(x, y));
    }

    // create menu, it's an autorelease object
    auto menu = Menu::create(closeItem, NULL);
    menu->setPosition(Vec2::ZERO);
    this->addChild(menu, 1);

    SpriteFrameCache::getInstance()->addSpriteFramesWithFile("sprites/lemmings.plist");
    auto walkFrames = GetAnimation("walk/%04d.png", 9);

    auto sprite = new Lemmings(walkFrames);
    this->addChild(sprite, 1);
    this->lemmingsList.push_back(sprite);

    //Cursor show
    this->cursorSprite = Sprite::create("sprites/cursor/0002.png");
    this->addChild(this->cursorSprite, 1);

    //Mouse listener
    auto mouseListener = EventListenerMouse::create();
    mouseListener->onMouseMove = [=](cocos2d::Event* event) {
        auto* mouseEvent = dynamic_cast<EventMouse*>(event);

        cursorX = mouseEvent->getCursorX();
        cursorY = mouseEvent->getCursorY();
        const Vec2 dotPos = { mouseEvent->getCursorX(), mouseEvent->getCursorY() };
        this->cursorSprite->setPosition(dotPos);

        if (mouseEvent->getMouseButton() == EventMouse::MouseButton::BUTTON_RIGHT) 
            this->cursorSprite->setTexture("sprites/cursor/0001.png");
        else
            this->cursorSprite->setTexture("sprites/cursor/0002.png");
    };
    _eventDispatcher->addEventListenerWithSceneGraphPriority(mouseListener, this);

    this->scheduleUpdate();
    return true;
}

void MainGame::update(float delta)
{
    Node::update(delta);

    for (auto lemming : lemmingsList)
    {
        lemming->move();
    }
}


void MainGame::menuCloseCallback(Ref* pSender)
{
    //Close the cocos2d-x game scene and quit the application
    Director::getInstance()->end();

    /*To navigate back to native iOS screen(if present) without quitting the application  ,do not use Director::getInstance()->end() as given above,instead trigger a custom event created in RootViewController.mm as below*/

    //EventCustom customEndEvent("game_scene_close_event");
    //_eventDispatcher->dispatchEvent(&customEndEvent);


}

cocos2d::Vector<cocos2d::SpriteFrame*> MainGame::GetAnimation(const char* format, int count)
{
    auto spritecache = SpriteFrameCache::getInstance();
    Vector<SpriteFrame*> animFrames;
    char str[100];
    for (int i = 1; i <= count; i++)
    {
        sprintf(str, format, i);
        animFrames.pushBack(spritecache->getSpriteFrameByName(str));
    }
    return animFrames;
}

bool MainGame::isKeyPressed(EventKeyboard::KeyCode code) {
    // Check if the key is pressed
    if (std::find(keys.begin(), keys.end(), code) != keys.end())
        return true;
    return false;
}

