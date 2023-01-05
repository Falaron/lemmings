#pragma once

#include "cocos2d.h"

enum LemmingActionName {
	DIG = 2,
	EXPLODE = 3,
	JUMP = 4,
	PARACHUTE = 6,
	STOP = 7
};

class LemmingAction : public::cocos2d::Sprite
{
public:

	void Initialize(int index, LemmingActionName action, int actionCount);
	CREATE_FUNC(LemmingAction);

	LemmingActionName GetAction() { return _action; };
	int GetIndex() { return _actionIndex; };

private:

	cocos2d::Label* _actionCountText;

	int _actionIndex;
	LemmingActionName _action;
	int _actionCount;
};

