#include "HUDLayer.h"
#include "GameManager.h"

std::vector<LemmingActionName> GameManager::_actions;
const std::string lemmingActionNames[] = { "build", "", "dig", "", "jump", "", "parachute", "stop" };

const float BORDER_WIDTH = 0.5f;
const float ACTION_SPRITE_SCALE_FACTOR = 1.25f;
const float ACTION_SPRITE_SIZE = 23.f;

USING_NS_CC;

bool HUDLayer::init()
{
	if (!Layer::init()) return false;

    cursorOnAction = 0;

	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

    frameCache = SpriteFrameCache::getInstance();
    frameCache->addSpriteFramesWithFile("sprites/lemmings/actions/actions.plist");
    frameCache->addSpriteFramesWithFile("sprites/lemmings/actions/actionsSelected.plist");

    setAnchorPoint(Vec2(0,0));

    auto backgroundNode = DrawNode::create();
    Vec2 rectangle[4];
    rectangle[0] = Vec2(40, 50);
    rectangle[1] = Vec2(440, 50);
    rectangle[2] = Vec2(440, 0);
    rectangle[3] = Vec2(40, 0);
    backgroundNode->drawPolygon(rectangle, 4, Color4F::BLACK, BORDER_WIDTH, Color4F::BLUE);
    this->addChild(backgroundNode);

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
    this->addChild(this->cursorSprite, 3);

    CreateActionsHUD();
    InitializeCursorMovementTrigger();

    this->scheduleUpdate();

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
    mouseListener->onMouseDown = [=](EventMouse* event) {
        if (event->getMouseButton() == EventMouse::MouseButton::BUTTON_LEFT) {
            if (cursorOnAction > -1)
            {
                GameManager::ChangeSelectedAction(actions[cursorOnAction]->GetAction());
            }
            else CCLOG("Selection %d", cursorOnAction);
        }
    };

    auto actions = getChildByName("ActionsContainer")->getChildren();

    _eventDispatcher->addEventListenerWithSceneGraphPriority(mouseListener, this);
}

void HUDLayer::CreateActionsHUD() {

    Node* actionsContainer = Node::create();
    actionsContainer->setName("ActionsContainer");
    addChild(actionsContainer);

    Vec2 rectangle[4];
    rectangle[0] = Vec2(0, 0);
    rectangle[1] = Vec2(0, ACTION_SPRITE_SIZE * ACTION_SPRITE_SCALE_FACTOR);
    rectangle[2] = Vec2(ACTION_SPRITE_SIZE * ACTION_SPRITE_SCALE_FACTOR, ACTION_SPRITE_SIZE * ACTION_SPRITE_SCALE_FACTOR);
    rectangle[3] = Vec2(ACTION_SPRITE_SIZE * ACTION_SPRITE_SCALE_FACTOR, 0);

    selectedFrameBorderAction = DrawNode::create();
    //selectedFrameBorderAction->setPosition(40, 0);
    selectedFrameBorderAction->drawPolygon(rectangle, 4, Color4F(0,0,0,0), BORDER_WIDTH, Color4F::RED);
    selectedFrameBorderAction->setAnchorPoint(Vec2(0, 0));
    selectedFrameBorderAction->setName("FrameBorder");
    actionsContainer->addChild(selectedFrameBorderAction, 2);

    for (int i = 0; i < GameManager::GetLemmingActions().size(); i++)
    {
        LemmingActionName action = GameManager::GetLemmingActions()[i];
        auto sprite = frameCache->getSpriteFrameByName(lemmingActionNames[action] + ".png");
        
        LemmingAction* lemmingActionSprite = LemmingAction::create();
        lemmingActionSprite->initWithSpriteFrame(sprite);
        lemmingActionSprite->Initialize(i, action);
        
        actions.push_back(lemmingActionSprite);
        actionsContainer->addChild(lemmingActionSprite);
    }

    actionsContainer->setPosition(BORDER_WIDTH, BORDER_WIDTH);
}

void HUDLayer::setCursorSprite(const char * sprite) {
    this->cursorSprite->setTexture(sprite);
}

void HUDLayer::UpdateSelectedActionBorder(int selectedAction)
{
    selectedFrameBorderAction->setPosition(40 + BORDER_WIDTH + (ACTION_SPRITE_SIZE * ACTION_SPRITE_SCALE_FACTOR * selectedAction), 0);
}

void HUDLayer::update(float delta) {
    Node::update(delta);

    for (auto action : actions) {
        if (cursorX >= action->getPosition().x && cursorX <= action->getPosition().x + ACTION_SPRITE_SIZE &&
            cursorY >= action->getPosition().y && cursorY <= action->getPosition().y + ACTION_SPRITE_SIZE)
        {
            cursorOnAction = action->GetIndex();
        }
        else cursorOnAction = -1;
    }
}
