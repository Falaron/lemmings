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

    // load the Sprite Sheet
    auto spritecache = SpriteFrameCache::getInstance();

    // the .plist file can be generated with any of the tools mentioned below
    spritecache->addSpriteFramesWithFile("sprites/lemmings.plist");

    _tileMap = TMXTiledMap::create("maps/test.tmx");
    addChild(_tileMap);
    _backGround = _tileMap->getLayer("ForeGround");
    _collision = _tileMap->getObjectGroup("MapCollisions");
    auto spawnPoint = _tileMap->getObjectGroup("SpawnPoint")->getObject("spawn");

    auto sprite = Sprite::create("sprites/flower.png");
    sprite->setPosition(spawnPoint["x"].asInt(), spawnPoint["y"].asInt());
    sprite->setPhysicsBody(PhysicsBody::createBox(sprite->getContentSize()));
    addChild(sprite);

    ValueVector& rectangles_array = _collision->getObjects();
    for (Value& rectangle : rectangles_array)
    {
        ValueMap rectangle_properties = rectangle.asValueMap();
        Node* node = Node::create();
        PhysicsBody* box = PhysicsBody::createEdgeBox(Size(rectangle_properties["width"].asInt(), rectangle_properties["height"].asInt()));
        node->setPhysicsBody(box);

        box->setGroup(1);

        node->setPosition(Vec2(rectangle_properties["x"].asInt() + rectangle_properties["width"].asInt() / 2, rectangle_properties["y"].asInt() + rectangle_properties["height"].asInt() / 2));

        box->setGravityEnable(false);
        box->setDynamic(false);

        this->addChild(node);
    }

    return true;
}


void MainGame::menuCloseCallback(Ref* pSender)
{
    //Close the cocos2d-x game scene and quit the application
    Director::getInstance()->end();

    /*To navigate back to native iOS screen(if present) without quitting the application  ,do not use Director::getInstance()->end() as given above,instead trigger a custom event created in RootViewController.mm as below*/

    //EventCustom customEndEvent("game_scene_close_event");
    //_eventDispatcher->dispatchEvent(&customEndEvent);


}
