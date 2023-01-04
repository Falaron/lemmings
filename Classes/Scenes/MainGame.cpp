#include "MainGame.h"

#define HUD_LAYER_NAME "HUDLayer"
#define GAME_LAYER_NAME "GameLayer"
#define CAMERA_STEP 25
#define CAMERA_MOVE_COOLDOWN 0.2

int GameManager::numberLemmingSpawn = 0;
int GameManager::numberLemmingExit = 0;
int GameManager::numberLemmingDead = 0;
LemmingAction GameManager::selectedAction;

USING_NS_CC;

Scene* MainGame::createScene()
{
    auto scene = MainGame::create();
    //scene->getPhysicsWorld()->setDebugDrawMask(cocos2d::PhysicsWorld::DEBUGDRAW_ALL);
    //scene->getPhysicsWorld()->setGravity(Vec2(0, -3));

    HUDLayer* hud = HUDLayer::create();
    hud->setName(HUD_LAYER_NAME);
    scene->addChild(hud, 1);

    GameLayer* gameLayer = GameLayer::create();
    gameLayer->setName(GAME_LAYER_NAME);
    scene->addChild(gameLayer);

    return scene;
}

// on "init" you need to initialize your instance
bool MainGame::init()
{
    if (!Scene::initWithPhysics()) return false;

    GameManager::SetLemmingSpawn(10);

    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    //Load available actions from level
    int actions[] = { DIG, PARACHUTE };
    for (int action : actions) {
        GameManager::AddAction((LemmingAction)action);
    }

    auto keyboardListener = EventListenerKeyboard::create();
    keyboardListener->onKeyPressed = [=](EventKeyboard::KeyCode keyCode, Event* event) {
        if (keyCode == EventKeyboard::KeyCode::KEY_ESCAPE) {
            auto pauseScene = PauseMenu::createScene();
            Director::getInstance()->pushScene(pauseScene);
        }
        
        switch (keyCode)
        {
        case cocos2d::EventKeyboard::KeyCode::KEY_LEFT_ARROW:
        case cocos2d::EventKeyboard::KeyCode::KEY_RIGHT_ARROW:
        case cocos2d::EventKeyboard::KeyCode::KEY_UP_ARROW:
        case cocos2d::EventKeyboard::KeyCode::KEY_DOWN_ARROW:
            keys.push_back(keyCode);
            break;
        }
    };

    keyboardListener->onKeyReleased = [=](EventKeyboard::KeyCode keyCode, Event* event) {
        // remove the key.
        keys.erase(std::remove(keys.begin(), keys.end(), keyCode), keys.end());
    };

    _eventDispatcher->addEventListenerWithSceneGraphPriority(keyboardListener, this);

    contactListener = EventListenerPhysicsContact::create();
    contactListener->onContactBegin = CC_CALLBACK_1(MainGame::onContactEnter, this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(contactListener, this);

    EventListenerPhysicsContact* contactListener1 = EventListenerPhysicsContact::create();
    contactListener1->onContactSeparate = CC_CALLBACK_1(MainGame::onContactExit, this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(contactListener1, this);

    this->scheduleUpdate();

    return true;
}

void MainGame::update(float delta)
{
    Node::update(delta);

    if (isKeyPressed(EventKeyboard::KeyCode::KEY_RIGHT_ARROW))
    {
        this->getDefaultCamera()->setPositionX(this->getDefaultCamera()->getPositionX() + CAMERA_STEP * delta);
        hudLayer->setPositionX(hudLayer->getPositionX() + CAMERA_STEP * delta);
    }
    if (isKeyPressed(EventKeyboard::KeyCode::KEY_LEFT_ARROW)) {
        this->getDefaultCamera()->setPositionX(this->getDefaultCamera()->getPositionX() - CAMERA_STEP * delta);
        hudLayer->setPositionX(hudLayer->getPositionX() - CAMERA_STEP * delta);
    }
    if (isKeyPressed(EventKeyboard::KeyCode::KEY_UP_ARROW)) {
        this->getDefaultCamera()->setPositionY(this->getDefaultCamera()->getPositionY() + CAMERA_STEP * delta);
        hudLayer->setPositionY(hudLayer->getPositionY() + CAMERA_STEP * delta);
    }
    if (isKeyPressed(EventKeyboard::KeyCode::KEY_DOWN_ARROW)) {
        this->getDefaultCamera()->setPositionY(this->getDefaultCamera()->getPositionY() - CAMERA_STEP * delta);
        hudLayer->setPositionY(hudLayer->getPositionY() - CAMERA_STEP * delta);
    }
   
}

bool MainGame::isKeyPressed(EventKeyboard::KeyCode code) {
    // Check if the key is pressed
    if (std::find(keys.begin(), keys.end(), code) != keys.end())
        return true;
    return false;
}

void MainGame::onEnterTransitionDidFinish()
{
    Node::onEnterTransitionDidFinish();

    this->hudLayer = (HUDLayer*)this->getChildByName(HUD_LAYER_NAME);
    this->gameLayer = (GameLayer*)this->getChildByName(GAME_LAYER_NAME);

    InitCamera();
}

void MainGame::InitCamera()
{
    auto defaultCamera = Director::getInstance()->getRunningScene()->getDefaultCamera();
    auto s = Director::getInstance()->getWinSize();

    Vec2 exitPos = gameLayer->GetExitPos();
    Size exitSize = gameLayer->GetExitSize();
    Vec2 spawnPos = gameLayer->GetSpawnPos();
    Size spawnSize = gameLayer->GetSpawnSize();

    int distX = (exitPos.x + exitSize.width) - (spawnPos.x + spawnSize.width);
    int distY = (spawnPos.y + spawnSize.height) - (exitPos.y + exitSize.height);
    int ratio;
    if (distX > distY) ratio = distX;
    else ratio = distY;
    ratio *= 2.0f;

    defaultCamera->initOrthographic(s.width, s.height, 1, 2000);
    defaultCamera->setPosition(0, 0);
    defaultCamera->setScale(ratio / s.width);
    hudLayer->setScale(ratio / s.width);
}

bool MainGame::onContactEnter(PhysicsContact& contact)
{
    auto shapeA = contact.getShapeA()->getBody()->getNode();
    auto shapeB = contact.getShapeB()->getBody()->getNode();

    if (shapeA && shapeB) {

        // EXIT DOOR COLLISION
        if (shapeA->getName() == "lemming" && shapeB->getName() == "exit door") {
            shapeA->removeFromParentAndCleanup(true);
            GameManager::IncreaseLemmingExit();
            hudLayer->updateLemmingsScore();
            if (GameManager::IsEndOfLevel())
                Director::getInstance()->replaceScene(EndLevelScene::createScene());
        }
        else if (shapeB->getName() == "lemming" && shapeA->getName() == "exit door") {
            shapeB->removeFromParentAndCleanup(true);
            GameManager::IncreaseLemmingExit();
            hudLayer->updateLemmingsScore();
            if (GameManager::IsEndOfLevel())
                Director::getInstance()->replaceScene(EndLevelScene::createScene());
        }


        // CURSOR COLLISION
        if (shapeA->getName() == "lemming" && shapeB->getName() == "cursor") {
            hudLayer->setCursorSprite("sprites/cursor/0001.png");
        }
        else if (shapeB->getName() == "lemming" && shapeA->getName() == "cursor") {
            hudLayer->setCursorSprite("sprites/cursor/0001.png");
        }
    }

    return true;
}

bool MainGame::onContactExit(PhysicsContact& contact)
{
    auto shapeA = contact.getShapeA()->getBody()->getNode();
    auto shapeB = contact.getShapeB()->getBody()->getNode();

    if (shapeA && shapeB) {

        // CURSOR COLLISION
        if (shapeA->getName() == "lemming" && shapeB->getName() == "cursor") {
            hudLayer->setCursorSprite("sprites/cursor/0002.png");
        }
        else if (shapeB->getName() == "lemming" && shapeA->getName() == "cursor") {
            hudLayer->setCursorSprite("sprites/cursor/0002.png");
        }
    }

    return true;
}