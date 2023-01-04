#include "HUDLayer.h"
#include "GameManager.h"

std::vector<LemmingAction> GameManager::_actions;

std::vector<LemmingAction> GameManager::_actions;
const std::string lemmingActionNames[] = { "build", "", "dig", "", "jump", "", "parachute", "stop" };
const float BORDER_WIDTH = 0.5f;

USING_NS_CC;

bool HUDLayer::init()
{
	if (!Layer::init()) return false;

	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

    frameCache = SpriteFrameCache::getInstance();
    frameCache->addSpriteFramesWithFile("sprites/lemmings/actions/actions.plist");
    frameCache->addSpriteFramesWithFile("sprites/lemmings/actions/actionsSelected.plist");

    setAnchorPoint(Vec2(0,0));

    auto rectNode = DrawNode::create();
    Vec2 rectangle[4];
    rectangle[0] = Vec2(40, 50);
    rectangle[1] = Vec2(440, 50);
    rectangle[2] = Vec2(440, 0);
    rectangle[3] = Vec2(40, 0);

    rectNode->drawPolygon(rectangle, 4, Color4F::BLACK, BORDER_WIDTH, Color4F::BLUE);
    this->addChild(rectNode);

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
    CreateActionsHUD();

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

    _eventDispatcher->addEventListenerWithSceneGraphPriority(mouseListener, this);
}

void HUDLayer::CreateActionsHUD() {

    Vector<MenuItem*> actionsItems;

    for (int i = 0; i < GameManager::GetLemmingActions().size(); i++)
    {
        LemmingAction action = GameManager::GetLemmingActions()[i];
        auto sprite = Sprite::createWithSpriteFrame(frameCache->getSpriteFrameByName(lemmingActionNames[action] + ".png"));
        auto spriteSelected = Sprite::createWithSpriteFrame(frameCache->getSpriteFrameByName(lemmingActionNames[action] + "-selected.png"));
        sprite->setScale(1.25f);
        sprite->setPositionX(40 + (i * sprite->getContentSize().width * sprite->getScale()));

        auto actionItem = MenuItemSprite::create(sprite, spriteSelected,
            [=](auto) {
                GameManager::ChangeSelectedAction(action);
            });
        actionItem->setAnchorPoint(Vec2::ZERO);
        actionsItems.pushBack(actionItem);
    }

    auto actionsHUD = Menu::createWithArray(actionsItems);
    actionsHUD->setPosition(Vec2(BORDER_WIDTH, BORDER_WIDTH));

    addChild(actionsHUD);
}
void HUDLayer::setCursorSprite(const char * sprite) {
    this->cursorSprite->setTexture(sprite);
}