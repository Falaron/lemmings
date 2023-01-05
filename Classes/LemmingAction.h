#pragma once

#include "cocos2d.h"
#include "GameManager.h"

class LemmingAction : public::cocos2d::Sprite
{
public:

	void Initialize(int index, LemmingActionName action);
	CREATE_FUNC(LemmingAction);

	LemmingActionName GetAction() { return _action; };
	int GetIndex() { return _actionIndex; };

private:

	int _actionIndex;
	LemmingActionName _action;
};

