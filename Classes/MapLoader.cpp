#include "MapLoader.h"

USING_NS_CC;

TMXTiledMap* MapLoader::_map = 0;
Scene* MapLoader::_scene = 0;
Vec2* MapLoader::_spawnPoint = 0;

void MapLoader::LoadMap(const char * mapName, Scene* currentScene)
{
    _scene = currentScene;
    _map = TMXTiledMap::create(mapName);
    _scene->addChild(_map);

    LoadMapCollisions();
    LoadSpawnPoint();
}


void MapLoader::LoadMapCollisions()
{
    cocos2d::TMXObjectGroup* collisions = _map->getObjectGroup("MapCollisions");

    ValueVector& collider_array = collisions->getObjects();
    for (Value& rectangle : collider_array)
    {
        ValueMap rectangle_properties = rectangle.asValueMap();
        Node* collider = Node::create();
        collider->setPosition(Vec2(rectangle_properties["x"].asInt() + rectangle_properties["width"].asInt() / 2, rectangle_properties["y"].asInt() + rectangle_properties["height"].asInt() / 2));

        PhysicsBody* box = PhysicsBody::createEdgeBox(Size(rectangle_properties["width"].asInt(), rectangle_properties["height"].asInt()), PHYSICSBODY_MATERIAL_DEFAULT, 0.5f);
        box->setGravityEnable(false);
        box->setDynamic(false);

        collider->setPhysicsBody(box);
        _scene->addChild(collider);
    }
}

void MapLoader::LoadSpawnPoint()
{
	auto spawnPointObject = _map->getObjectGroup("SpawnPoint")->getObject("spawn");
    _spawnPoint = new Vec2(spawnPointObject["x"].asInt(), spawnPointObject["y"].asInt());
}
