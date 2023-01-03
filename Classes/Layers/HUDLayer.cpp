#include "HUDLayer.h"
#include "GameManager.h"

std::vector<LemmingAction> GameManager::_actions;

const std::string lemmingActionNames[] = { "build", "", "dig", "", "jump", "", "parachute", "stop" };

USING_NS_CC;

bool HUDLayer::init()
{
	if (!Layer::init()) return false;

	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();


    frameCache = SpriteFrameCache::getInstance();
    frameCache->addSpriteFramesWithFile("sprites/lemmings/actions/actions.plist");

    setAnchorPoint(Vec2(0,0));

    for (int i = 0 ; i < GameManager::GetLemmingActions().size() ; i++)
    {
        LemmingAction action = GameManager::GetLemmingActions()[i];
        auto sprite = Sprite::createWithSpriteFrame(frameCache->getSpriteFrameByName(lemmingActionNames[action] + ".png"));
        sprite->setAnchorPoint(Vec2(0, 0));
        sprite->setPosition(i * 50, 0);
        addChild(sprite);
    }

    //Cursor show
    this->cursorSprite = Sprite::create("sprites/cursor/0002.png");
    this->cursorSprite->setScale(2);
    this->cursorSprite->setName("cursor");

    PhysicsBody* box = PhysicsBody::createBox(cursorSprite->getContentSize(), PhysicsMaterial(0.2f, 0, 0));
    box->setGravityEnable(false);
    box->setDynamic(false);
    box->setRotationEnable(false);
    box->setContactTestBitmask(0xEEEEEEEE);
    box->setCollisionBitmask(0);

    cursorSprite->addComponent(box);
    this->addChild(this->cursorSprite);

    InitializeCursorMovementTrigger();

    return true;
}

void HUDLayer::InitializeCursorMovementTrigger() {
    //Create a mouse listener
    auto mouseListener = EventListenerMouse::create();

    // Move mouse listener
    mouseListener->onMouseMove = [=](cocos2d::Event* event) {
        auto* mouseEvent = dynamic_cast<EventMouse*>(event);

        cursorX = mouseEvent->getCursorX();
        cursorY = mouseEvent->getCursorY();
        cursorSprite->setPosition(cursorX, cursorY);
    };


    // Click mouse listener
    /*mouseListener->onMouseDown = [=](EventMouse* event) {
        if (event->getMouseButton() == EventMouse::MouseButton::BUTTON_RIGHT) {
            this->cursorSprite->setTexture("sprites/cursor/0001.png");
        }
    };
    mouseListener->onMouseUp = [=](EventMouse* event) {
        if (event->getMouseButton() == EventMouse::MouseButton::BUTTON_RIGHT) {
            this->cursorSprite->setTexture("sprites/cursor/0002.png");
        }
    };*/
    _eventDispatcher->addEventListenerWithSceneGraphPriority(mouseListener, this);
}

void HUDLayer::setCursorSprite(const char * sprite) {
    this->cursorSprite->setTexture(sprite);
}