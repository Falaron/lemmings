#include "MapLoader.h"
#include "LevelRegistry.h"
#include "GameManager.h"

USING_NS_CC;

const float TilesSize = 15.37f;
TMXTiledMap* MapLoader::_map = 0;
Layer* MapLoader::_layer = 0;
Vec2* MapLoader::_spawnPoint = 0;
Vec2* MapLoader::_exitpoint = 0;
std::vector<cocos2d::Node*> MapLoader::_blockList;

void MapLoader::LoadMap(Layer* currentLayer)
{
    _layer = currentLayer;
    _map = TMXTiledMap::create("maps/map" + std::to_string(GameManager::GetCurrentLevel()+1) + ".tmx");
    _layer->addChild(_map);

    LoadMapCollisions();
    LoadSpawnPoint();
    LoadExitPoint();
    LoadDeadCollision();
}

cocos2d::TMXLayer* MapLoader::GetLayer(std::string layer)
{
    return _map->getLayer(layer);
}


void MapLoader::LoadMapCollisions()
{
    cocos2d::TMXObjectGroup* collisions = _map->getObjectGroup("MapCollisions");

    ValueVector& collider_array = collisions->getObjects();

    for (Value& rectangle : collider_array)
    {
        ValueMap rectangle_properties = rectangle.asValueMap();

        float posX = rectangle_properties["x"].asFloat();
        float posY = rectangle_properties["y"].asFloat();

        for (int i = 0; i < rectangle_properties["height"].asFloat() / TilesSize; i++)
        {
            for (int y = 0; y < rectangle_properties["width"].asFloat() / TilesSize ; y++)
            {
                Node* collider = Node::create();
                collider->setPosition(Vec2((posX + y * TilesSize) + TilesSize / 2, (posY + i * TilesSize) + TilesSize / 2));

                PhysicsBody* box = PhysicsBody::createEdgeBox(Size(TilesSize, TilesSize), PhysicsMaterial(0,0,0), 0.5f);
                box->setGravityEnable(false);
                box->setDynamic(false);
                box->setGroup(1);
                box->setContactTestBitmask(0xEEEEEEEE);

                collider->setName("ground");
                collider->setPhysicsBody(box);
                _layer->addChild(collider);
                _blockList.push_back(collider);
            }
        }
        
    }
}

void MapLoader::LoadSpawnPoint()
{
	auto spawnPointObject = _map->getObjectGroup("Meta")->getObject("spawnPoint");
    _spawnPoint = new Vec2(spawnPointObject["x"].asInt(), spawnPointObject["y"].asInt());
}

void MapLoader::LoadExitPoint()
{
    auto exitPointObject = _map->getObjectGroup("Meta")->getObject("exitPoint");
    _exitpoint = new Vec2(exitPointObject["x"].asInt(), exitPointObject["y"].asInt());
}

void MapLoader::LoadDeadCollision() {

    cocos2d::TMXObjectGroup* deathCollisions = _map->getObjectGroup("MapDeathObjects");

    if (!deathCollisions) return;

    ValueVector& collider_array = deathCollisions->getObjects();
    for (Value& rectangle : collider_array)
    {
        ValueMap rectangle_properties = rectangle.asValueMap();

        float posX = rectangle_properties["x"].asFloat();
        float posY = rectangle_properties["y"].asFloat();

        for (int i = 0; i < rectangle_properties["height"].asFloat() / TilesSize; i++)
        {
            for (int y = 0; y < rectangle_properties["width"].asFloat() / TilesSize; y++)
            {
                Node* deathCollider = Node::create();
                deathCollider->setPosition(Vec2((posX + y * TilesSize) + TilesSize / 2, (posY + i * TilesSize) + TilesSize / 2));
                deathCollider->setName("deathCollider");

                PhysicsBody* box = PhysicsBody::createEdgeBox(Size(TilesSize, TilesSize), PhysicsMaterial(0, .3f, 0), 0.5f);
                box->setGravityEnable(false);
                box->setDynamic(false);
                box->setGroup(1);
                box->setContactTestBitmask(0xEEEEEEEE);

                deathCollider->setPhysicsBody(box);
                _layer->addChild(deathCollider);
            }
        }
    }
}

void MapLoader::LoadLevelInfo()
{
    int val = GameManager::GetCurrentLevel();
    Level currentLevel = LevelRegistry::GetLevel(GameManager::GetCurrentLevel());
    GameManager::SetLemmingSpawn(currentLevel.GetLemmingsToSpawn());
    GameManager::SetLemmingVictory(currentLevel.GetRequiredLemmingsToWin());
    GameManager::setTimer(currentLevel.GetMinutes(), currentLevel.GetSeconds());

    for (auto action : currentLevel.GetActions())
    {
        GameManager::AddAction(action);
    }
}

cocos2d::Vec2* MapLoader::NormalizePosition(cocos2d::Vec2 position)
{
    int posX = ((int)position.x / TilesSize);
    int posY = ((int)position.y / TilesSize);

    auto test = new Vec2(posX, posY);

    return test;
}

void MapLoader::DeleteTile(cocos2d::Vec2 deletepos)
{
    Size size = _map->getMapSize();
    if (deletepos.x > 0 && deletepos.x < size.width && deletepos.y > 0 && deletepos.y < size.height) {

        for (auto block : _blockList) {
            auto position = NormalizePosition(block->getPosition());
            if (*position == deletepos) {
                _blockList.erase(std::remove(_blockList.begin(), _blockList.end(), block), _blockList.end());
                block->removeFromParentAndCleanup(true);
            }
        }
        auto layer = MapLoader::GetLayer("Foreground");

        deletepos.y = (layer->getLayerSize().height - 1) - deletepos.y;
        layer->removeTileAt(deletepos);
    }
}