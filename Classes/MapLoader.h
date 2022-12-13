#pragma once
#include "cocos2d.h"

class MapLoader {

public:

	static void LoadMap(const char *, cocos2d::Scene*);
	static cocos2d::TMXTiledMap* GetLoadedMap() { return _map; };


private:

	static void LoadMapCollisions();
	static void LoadSpawnPoint();

	static cocos2d::Scene* _scene;
	static cocos2d::TMXTiledMap* _map;

	static cocos2d::Vec2* _spawnPoint;
};