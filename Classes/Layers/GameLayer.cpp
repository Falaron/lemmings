#include "GameLayer.h"
#include "HUDLayer.h"

#include "MapLoader.h"
#include "GameManager.h"

USING_NS_CC;

bool GameLayer::init()
{
	if (!Layer::init()) return false;

    MapLoader::LoadMap(this);

	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

    frameCache = SpriteFrameCache::getInstance();
    physicCache = PhysicsShapeCache::getInstance();

    frameCache->addSpriteFramesWithFile("sprites/lemmings.plist");
    physicCache->getInstance()->removeAllShapes();
    physicCache->addShapesWithFile("sprites/exit-door.plist");


    InitSpawnAndExit();
    SpawnLemmings();

    this->scheduleUpdate();

    return true;
}

void GameLayer::update(float delta) {
    Node::update(delta);

    for (auto lemming : lemmingsList)
    {
        lemming->Update();
        if (!lemming->isInMap() || lemming->GetState() == DEAD) {
            RemoveLemming(lemming);
        }
    }
}

void GameLayer::SpawnLemmings() {
    for (int i = 0; i < GameManager::GetLemmingSpawn(); i++) {
        cocos2d::CallFunc* A = cocos2d::CallFunc::create([=]() {
            Lemmings* lemming = new Lemmings();
            this->addChild(lemming, 1);
            this->lemmingsList.push_back(lemming);
        });
        cocos2d::DelayTime* delay = cocos2d::DelayTime::create(i);
        runAction(cocos2d::Sequence::create(delay, A, NULL));
    }
}

void GameLayer::RemoveLemming(Lemmings* lemming)
{
    lemmingsList.erase(std::remove(lemmingsList.begin(), lemmingsList.end(), lemming), lemmingsList.end());
    lemming->removeFromParentAndCleanup(true);
    delete lemming;
    GameManager::IncreaseLemmingDead();
    ((HUDLayer*)Director::getInstance()->getRunningScene()->getChildByName(HUD_LAYER_NAME))->updateLemmingsScore();
}

void GameLayer::InitSpawnAndExit()
{
    _spawn = Sprite::create("sprites/spawn-door.png");
    _spawn->setPosition(*MapLoader::GetSpawnPoint());
    this->addChild(_spawn);

    _exit = Sprite::create("sprites/exit-door.png");
    physicCache->setBodyOnSprite("exit-door", _exit);
    this->addChild(_exit);
    _exit->setAnchorPoint(Vec2(0.5, 0));
    _exit->setPosition(*MapLoader::GetExitPoint());
    _exit->getPhysicsBody()->setContactTestBitmask(0xEEEEEEEE);
    _exit->setName("exit door");
}
