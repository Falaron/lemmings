#include "GameManager.h"
#include "cocos/base/CCDirector.h"
#include "Scenes/EndLevelScene.h"

void GameManager::IncreaseLemmingExit()
{
	numberLemmingExit++;
	checkEndLevel();
}

void GameManager::IncreaseLemmingDead()
{
	numberLemmingDead++;
	checkEndLevel();
}

void GameManager::checkEndLevel()
{
	if (numberLemmingDead + numberLemmingExit >= numberLemmingSpawn)
		cocos2d::Director::getInstance()->replaceScene(EndLevelScene::createScene());
}

void GameManager::Reset()
{
	numberLemmingDead = 0;
	numberLemmingExit = 0;
	numberLemmingVictory = 0;
	numberLemmingSpawn = 0;

	_seconds = 0;
	_minutes = 0;

	_actions.clear();
}
