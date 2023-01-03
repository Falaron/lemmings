#include "MapLoader.h"

USING_NS_CC;

const float TilesSize = 15.37f;
TMXTiledMap* MapLoader::_map = 0;
Layer* MapLoader::_layer = 0;
Vec2* MapLoader::_spawnPoint = 0;
Vec2* MapLoader::_exitpoint = 0;

void MapLoader::LoadMap(const char * mapName, Layer* currentLayer)
{
    _layer = currentLayer;
    _map = TMXTiledMap::create(mapName);
    _layer->addChild(_map);

    LoadMapCollisions();
    LoadSpawnPoint();
    LoadExitPoint();
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

                collider->setPhysicsBody(box);
                _layer->addChild(collider);
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
