#include "HUDLayer.h"
#include "GameManager.h"
#include "Scenes/EndLevelScene.h"

std::vector<std::pair<LemmingActionName, int>> GameManager::_actions;
const std::string lemmingActionNames[] = { "build", "", "dig", "explode", "jump", "", "parachute", "stop" };

const float BORDER_WIDTH = 0.5f;
const float ACTION_SPRITE_SCALE_FACTOR = 1.25f;
const float ACTION_SPRITE_SIZE = 23.f;

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

    //Create background
    auto backgroundNode = DrawNode::create();
    Vec2 rectangle[4];
    rectangle[0] = Vec2(40, 50);
    rectangle[1] = Vec2(440, 50);
    rectangle[2] = Vec2(440, 0);
    rectangle[3] = Vec2(40, 0);
    backgroundNode->drawPolygon(rectangle, 4, Color4F::BLACK, BORDER_WIDTH, Color4F::BLUE);
    this->addChild(backgroundNode);

    //Show infos
    lemmingsInGameText = Label::createWithSystemFont("OUT " + std::to_string(GameManager::GetLemmingSpawn() - (GameManager::GetLemmingDead() + GameManager::GetLemmingExit())), "fonts/arial.ttf", 20);
    lemmingsInGameText->setPosition(Vec2(200, 35));
    this->addChild(lemmingsInGameText);

    lemmingsEscapedText = Label::createWithSystemFont("IN " + std::to_string(int(float(GameManager::GetLemmingExit()) / GameManager::GetLemmingSpawn() * 100)) + "%", "fonts/arial.ttf", 20);
    lemmingsEscapedText->setPosition(Vec2(275, 35));
    this->addChild(lemmingsEscapedText);

    //Show timer
    this->schedule(CC_SCHEDULE_SELECTOR(HUDLayer::ticktock), 1.0f);
    timer = Label::createWithSystemFont("TIME " + std::to_string(GameManager::getMinutes()) + " - " + std::to_string(GameManager::getSeconds()), "fonts/arial.ttf", 20);
    timer->setPosition(Vec2(375, 35));
    this->addChild(timer);

    
    LemmingvictoryText = Label::createWithSystemFont("VICTORY " + std::to_string(int(float(GameManager::GetLemmingVictory()) / GameManager::GetLemmingSpawn() * 100)) + "%", "fonts/arial.ttf", 20);
    LemmingvictoryText->setPosition(Vec2(360, 10));
    this->addChild(LemmingvictoryText);

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

    selectedAction = actions[0];
    UpdateSelectedActionBorder(0);

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
            if (isCursorOnAction)
            {
                selectedAction = actions[cursorOnActionIndex];

                CCLOG("Action selected %d with %d", selectedAction->GetAction(), selectedAction->GetCount());
                GameManager::ChangeSelectedAction(selectedAction->GetAction());
                UpdateSelectedActionBorder(cursorOnActionIndex);
            }
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
    selectedFrameBorderAction->drawPolygon(rectangle, 4, Color4F(0,0,0,0), BORDER_WIDTH, Color4F::RED);
    selectedFrameBorderAction->setAnchorPoint(Vec2(0, 0));
    selectedFrameBorderAction->setName("FrameBorder");
    actionsContainer->addChild(selectedFrameBorderAction, 2);

    //Create UI sprite for each action
    for (int i = 0; i < GameManager::GetLemmingActions().size(); i++)
    {
        std::pair<LemmingActionName, int> action = GameManager::GetLemmingActions()[i];
        auto sprite = frameCache->getSpriteFrameByName(lemmingActionNames[action.first] + ".png");
        
        LemmingAction* lemmingActionSprite = LemmingAction::create();
        lemmingActionSprite->initWithSpriteFrame(sprite);
        lemmingActionSprite->Initialize(i, action.first, action.second);
        
        actions.push_back(lemmingActionSprite);
        actionsContainer->addChild(lemmingActionSprite);
    }

    actionsContainer->setPosition(BORDER_WIDTH, BORDER_WIDTH);
}

void HUDLayer::SwitchCursorSprite(const char * sprite) {
    this->cursorSprite->setTexture(sprite);
}

void HUDLayer::UpdateSelectedActionBorder(int selectedActionIndex)
{
    selectedFrameBorderAction->setPositionX(40 + BORDER_WIDTH + (ACTION_SPRITE_SIZE * ACTION_SPRITE_SCALE_FACTOR * selectedActionIndex));
}

void HUDLayer::UpdateActionCount()
{
    if (selectedAction->GetCount() > 0)
    {
        selectedAction->DecreaseCount();
        ((Label*)selectedAction->getChildByName("count"))->setString(std::to_string(selectedAction->GetCount()));
    }
}

void HUDLayer::update(float delta) {
    Node::update(delta);

    isCursorOnAction = false;

    for (auto action : actions) {
        if (cursorX >= action->getPosition().x && cursorX <= action->getPosition().x + ACTION_SPRITE_SIZE * ACTION_SPRITE_SCALE_FACTOR &&
            cursorY >= action->getPosition().y && cursorY <= action->getPosition().y + ACTION_SPRITE_SIZE * ACTION_SPRITE_SCALE_FACTOR)
        {
            isCursorOnAction = true;
            cursorOnActionIndex = action->GetIndex();
        }
    }
}

void HUDLayer::ticktock(float dt) {
    if (GameManager::getSeconds() <= 0) {
        GameManager::decreaseMinutes();
        GameManager::reloadSeconds();
    }
    else GameManager::decreaseSeconds();
    timer->setString("TIME " + std::to_string(GameManager::getMinutes()) + " - " + std::to_string(GameManager::getSeconds()));

    if (GameManager::getMinutes() + GameManager::getSeconds() <= 0)
        cocos2d::Director::getInstance()->replaceScene(EndLevelScene::createScene());
}

void HUDLayer::updateLemmingsScore() {
    lemmingsInGameText->setString("OUT " + std::to_string(GameManager::GetLemmingSpawn() - (GameManager::GetLemmingDead() + GameManager::GetLemmingExit())));
    lemmingsEscapedText->setString("IN " + std::to_string(int(float(GameManager::GetLemmingExit()) / GameManager::GetLemmingSpawn() * 100)) + "%");
}