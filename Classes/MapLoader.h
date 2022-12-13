#pragma once
#include "cocos2d.h"

class MapLoader {

public:

	static void LoadMap(const char *, cocos2d::Layer*);

	static cocos2d::TMXTiledMap* GetLoadedMap() { return _map; };
	static cocos2d::Vec2* GetSpawnPoint() { return _spawnPoint; };
	static cocos2d::Vec2* GetExitPoint() { return _exitpoint; };


private:

	static void LoadMapCollisions();
	static void LoadSpawnPoint();
	static void LoadExitPoint();

	static cocos2d::Layer* _layer;
	static cocos2d::TMXTiledMap* _map;

	static cocos2d::Vec2* _spawnPoint;
	static cocos2d::Vec2* _exitpoint;
};