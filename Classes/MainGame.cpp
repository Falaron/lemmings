#include "MainGame.h"

USING_NS_CC;

Scene* MainGame::createScene()
{
    auto scene = Scene::createWithPhysics();
    //scene->getPhysicsWorld()->setDebugDrawMask(cocos2d::PhysicsWorld::DEBUGDRAW_ALL);
    //scene->getPhysicsWorld()->setGravity(Vec2(0, -3));
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
    if (!Layer::init()) return false;

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

    physicCache = PhysicsShapeCache::getInstance();
    frameCache = SpriteFrameCache::getInstance();

    frameCache->addSpriteFramesWithFile("sprites/lemmings.plist");

   
    

    for (int i = 0; i < 10; i++) {
        cocos2d::CallFunc* A = cocos2d::CallFunc::create([=]() {
            auto lemming = new Lemmings();
            this->addChild(lemming, 2);
            this->lemmingsList.push_back(lemming);
            });
        cocos2d::DelayTime* delay = cocos2d::DelayTime::create(i);
        runAction(cocos2d::Sequence::create(delay,A, NULL));
    }

    CCLOG("length : %d", this->lemmingsList.size());

    //Cursor show
    this->cursorSprite = Sprite::create("sprites/cursor/0002.png");
    this->addChild(this->cursorSprite, 2);

    auto shapeCache = PhysicsShapeCache::getInstance();
    shapeCache->addShapesWithFile("sprites/exit-door.plist");

    InitSpawnAndExit();
    InitCamera();

    //Mouse listener
    auto mouseListener = EventListenerMouse::create();
    mouseListener->onMouseMove = [=](cocos2d::Event* event) {
        auto* mouseEvent = dynamic_cast<EventMouse*>(event);

        cursorX = mouseEvent->getCursorX();
        cursorY = mouseEvent->getCursorY();
        this->cursorSprite->setPosition(cursorX, cursorY);

        if (mouseEvent->getMouseButton() == EventMouse::MouseButton::BUTTON_RIGHT) 
            this->cursorSprite->setTexture("sprites/cursor/0001.png");
        else
            this->cursorSprite->setTexture("sprites/cursor/0002.png");
    };
    _eventDispatcher->addEventListenerWithSceneGraphPriority(mouseListener, this);

    auto keyboardListener = EventListenerKeyboard::create();
    keyboardListener->onKeyPressed = [](EventKeyboard::KeyCode keyCode, Event* event) {
        if (keyCode == EventKeyboard::KeyCode::KEY_ESCAPE) {
            auto pauseScene = PauseMenu::createScene();
            Director::getInstance()->pushScene(TransitionFade::create(.2f, pauseScene));
        }
    };

    this->_eventDispatcher->addEventListenerWithSceneGraphPriority(keyboardListener, this);

    this->scheduleUpdate();
    return true;
}

void MainGame::onEnter()
{
    Layer::onEnter();
    

    //changed static zoom to distance between spawn and ecit
}

void MainGame::update(float delta)
{
    Node::update(delta);
    CCLOG("for");
    for (auto lemming : lemmingsList)
    {
        lemming->Move();
        if (!lemming->isInMap()) {
            lemmingsList.erase(std::remove(lemmingsList.begin(),lemmingsList.end(), lemming),lemmingsList.end());
            lemming->removeFromParentAndCleanup(true);
            CCLOG("delete");
        }
    }
}


void MainGame::menuCloseCallback(Ref* pSender)
{
    //Close the cocos2d-x game scene and quit the application
    Director::getInstance()->end();
}

void MainGame::InitCamera()
{
    auto defaultCamera = Director::getInstance()->getRunningScene()->getDefaultCamera();

    auto s = Director::getInstance()->getWinSize();
    Vec2 exitPos = _exit->getPosition();
    Size exitSize = _exit->getContentSize();
    Vec2 spawnPos = _spawn->getPosition();
    Size spawnSize = _spawn->getContentSize();

    int distX = (exitPos.x + exitSize.width) - (spawnPos.x + spawnSize.width);
    int distY = (spawnPos.y + spawnSize.height) - (exitPos.y + exitSize.height);
    int ratio;
    if (distX > distY) ratio = distX;
    else ratio = distY;
    ratio *= 1.66;

    CCLOG("distX:%d | distY:%d", distX, distY);

    defaultCamera->initOrthographic(s.width, s.height, 1, 2000);
    defaultCamera->setPosition(spawnPos.x - spawnSize.width, exitPos.y - exitSize.height);
    defaultCamera->setScale(ratio / s.width);
}

void MainGame::InitSpawnAndExit()
{
    _spawn = Sprite::create("sprites/spawn-door.png");
    _spawn->setPosition(*MapLoader::GetSpawnPoint());
    this->addChild(_spawn, 1);

    _exit = Sprite::create("sprites/exit-door.png");
    physicCache->setBodyOnSprite("exit-door", _exit);
    this->addChild(_exit, 1);
    _exit->setAnchorPoint(Vec2(0.5, 0));
    _exit->setPosition(*MapLoader::GetExitPoint());

}

bool MainGame::isKeyPressed(EventKeyboard::KeyCode code) {
    // Check if the key is pressed
    if (std::find(keys.begin(), keys.end(), code) != keys.end())
        return true;
    return false;
}
