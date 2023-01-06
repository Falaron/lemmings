#include "MainGame.h"
#include "LemmingAction.h"
#include "LevelRegistry.h"
#include "MapLoader.h"

#define CAMERA_PAN_OFFSET 50
#define CAMERA_STEP 25
#define CAMERA_MOVE_COOLDOWN 0.2

int GameManager::numberLemmingSpawn = 0;
int GameManager::numberLemmingExit = 0;
int GameManager::numberLemmingDead = 0;
int GameManager::numberLemmingVictory = 5;
int GameManager::currentLevel = 0;
float GameManager::_minutes = 0;
float GameManager::_seconds = 0;

LemmingActionName GameManager::selectedAction;

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

    mouseDown = false;

    windowSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    MapLoader::LoadLevelInfo();

    contactListener = EventListenerPhysicsContact::create();
    contactListener->onContactBegin = CC_CALLBACK_1(MainGame::onContactEnter, this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(contactListener, this);

    EventListenerPhysicsContact* contactListener1 = EventListenerPhysicsContact::create();
    contactListener1->onContactSeparate = CC_CALLBACK_1(MainGame::onContactExit, this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(contactListener1, this);

    this->scheduleUpdate();

    //Create a mouse listener
    mouseListener = EventListenerMouse::create();

    mouseListener->onMouseDown = [=](EventMouse* event) {
        mouseDown = true;
    };

    mouseListener->onMouseUp = [=](EventMouse* event) {
        mouseDown = false;
    };

    _eventDispatcher->addEventListenerWithSceneGraphPriority(mouseListener, this);

    return true;
}

void MainGame::update(float delta)
{
    Node::update(delta);

    if (hudLayer->GetCursorX() <= CAMERA_PAN_OFFSET + 40 && hudLayer->GetCursorY() >= 50) // LEFT CAMERA PAN 
    {
        getDefaultCamera()->setPositionX(getDefaultCamera()->getPositionX() - CAMERA_STEP * delta);
        hudLayer->setPositionX(hudLayer->getPositionX() - CAMERA_STEP * delta);
    }
    else if (hudLayer->GetCursorX() >= windowSize.width - CAMERA_PAN_OFFSET + 20 && hudLayer->GetCursorY() >= 50) // RIGHT CAMERA PAN 
    {
        getDefaultCamera()->setPositionX(getDefaultCamera()->getPositionX() + CAMERA_STEP * delta);
        hudLayer->setPositionX(hudLayer->getPositionX() + CAMERA_STEP * delta);
    }

    if (hudLayer->GetCursorY() <= CAMERA_PAN_OFFSET * 2 && hudLayer->GetCursorY() >= 50 ) // DOWN CAMERA PAN 
    {
        getDefaultCamera()->setPositionY(getDefaultCamera()->getPositionY() - CAMERA_STEP * delta);
        hudLayer->setPositionY(hudLayer->getPositionY() - CAMERA_STEP * delta);
    }
    else if (hudLayer->GetCursorY() >= windowSize.height - CAMERA_PAN_OFFSET) // UP CAMERA PAN 
    {
        getDefaultCamera()->setPositionY(getDefaultCamera()->getPositionY() + CAMERA_STEP * delta);
        hudLayer->setPositionY(hudLayer->getPositionY() + CAMERA_STEP * delta);
    }

    if (mouseDown && selectedLemmings) {
        state lemmingState = selectedLemmings->GetState();
        if (lemmingState == MOVING && hudLayer->GetSelectedAction()->GetCount() > 0) {
            LemmingActionName action = GameManager::getSelectedAction();
            if (action == DIG) {
                selectedLemmings->SetState(DIGGING);
            }
            else if (action == HORIZONTALDIG) {
                selectedLemmings->SetState(HORIZONTALDIGGING);
            }
            else if (action == EXPLODE) {
                selectedLemmings->SetState(BOMBING);
            }
            else if (action == JUMP) {
                selectedLemmings->SetState(JUMPING);
            }
            else if (action == PARACHUTE) {
                selectedLemmings->SetState(PARACHUTING);
            }

            hudLayer->UpdateActionCount();
        }
    }
}

void MainGame::onEnterTransitionDidFinish()
{
    Node::onEnterTransitionDidFinish();

    this->hudLayer = (HUDLayer*)this->getChildByName(HUD_LAYER_NAME);
    this->gameLayer = (GameLayer*)this->getChildByName(GAME_LAYER_NAME);
    gameLayer->setScale(1.5);
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

    defaultCamera->initOrthographic(s.width, s.height, 1, 2000);
    defaultCamera->setPosition((spawnPos.x - s.width/2), (spawnPos.y - s.height/2));
    hudLayer->setPosition((spawnPos.x - s.width/2), (spawnPos.y - s.height/2));
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
            return true;
        }
        else if (shapeB->getName() == "lemming" && shapeA->getName() == "exit door") {
            shapeB->removeFromParentAndCleanup(true);
            GameManager::IncreaseLemmingExit();
            hudLayer->updateLemmingsScore();
            return true;
        }

        // CURSOR COLLISION
        if (shapeA->getName() == "lemming" && shapeB->getName() == "cursor") {
            hudLayer->IncreaseLemmingInCursor();
            if (hudLayer->GetLemmingsInCursor() == 1)
            {
                hudLayer->SwitchCursorSprite("sprites/cursor/0001.png");
            }

            selectedLemmings = (Lemmings*)shapeA;
        }
        else if (shapeB->getName() == "lemming" && shapeA->getName() == "cursor") {
            hudLayer->IncreaseLemmingInCursor();
            if (hudLayer->GetLemmingsInCursor() == 1)
            {
                hudLayer->SwitchCursorSprite("sprites/cursor/0001.png");
            }

            selectedLemmings = (Lemmings*)shapeB;
        }

        //DEATH COLLISION
        if (shapeB->getName() == "lemming" && shapeA->getName() == "deathCollider") {
            shapeB->getPhysicsBody()->setContactTestBitmask(0);
            GameManager::IncreaseLemmingDead();
            hudLayer->updateLemmingsScore();

            cocos2d::CallFunc* A = cocos2d::CallFunc::create([=]() {
                shapeB->removeFromParentAndCleanup(true);
                });
            cocos2d::DelayTime* delay = cocos2d::DelayTime::create(1);
            this->runAction(Sequence::create(delay, A, NULL));
        }

        if (shapeB->getTag() == 5 && shapeA->getName() == "cursor") {
            GameManager::ChangeSelectedAction(((LemmingAction*)shapeA)->GetAction());
            hudLayer->UpdateSelectedActionBorder(((LemmingAction*)shapeA)->GetIndex());
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
            hudLayer->DecreaseLemmingInCursor();
            if (hudLayer->GetLemmingsInCursor() == 0)
            {
                hudLayer->SwitchCursorSprite("sprites/cursor/0002.png");
            }

            if (hudLayer->GetLemmingsInCursor() < 1)
            {
                selectedLemmings = NULL;
            }
        }
        else if (shapeB->getName() == "lemming" && shapeA->getName() == "cursor") {
            hudLayer->DecreaseLemmingInCursor();
            if (hudLayer->GetLemmingsInCursor() == 0)
            {
                hudLayer->SwitchCursorSprite("sprites/cursor/0002.png");
            }

            if (hudLayer->GetLemmingsInCursor() < 1)
            {
                selectedLemmings = NULL;
            }
        }
    }

    return true;
}