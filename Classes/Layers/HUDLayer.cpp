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
    this->cursorSprite->setScale(4);
    this->addChild(this->cursorSprite);    

    InitializeCursorMovementTrigger();

    return true;
}

void HUDLayer::InitializeCursorMovementTrigger() {
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
}
