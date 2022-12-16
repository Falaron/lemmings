#include "HUDLayer.h"

USING_NS_CC;

bool HUDLayer::init()
{
	if (!Layer::init()) return false;

	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

    comboLabel1 = Label::createWithTTF("COUCOU", "fonts/arial.ttf", visibleSize.height * 0.1);
    comboLabel1->setColor(Color3B::WHITE);
    comboLabel1->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));
    setAnchorPoint(Vec2(0,0));

    addChild(comboLabel1);

    //Cursor show
    this->cursorSprite = Sprite::create("sprites/cursor/0002.png");
    this->cursorSprite->setScale(4);
    this->addChild(this->cursorSprite);

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

    return true;
}
