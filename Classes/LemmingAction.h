#pragma once

#include "cocos2d.h"

enum LemmingActionName {
	DIG = 0,
	EXPLODE = 2,
	JUMP = 3,
	PARACHUTE = 5,
	HORIZONTALDIG = 1
};

class LemmingAction : public::cocos2d::Sprite
{
public:

	void Initialize(int index, LemmingActionName action, int actionCount);
	CREATE_FUNC(LemmingAction);

	LemmingActionName GetAction() { return _action; };
	int GetIndex() { return _actionIndex; };
	int GetCount() { return _actionCount; };

	void DecreaseCount() {  _actionCount--; };

private:

	LemmingActionName _action;
	cocos2d::Label* _actionCountText;

	int _actionIndex;
	int _actionCount;
};

