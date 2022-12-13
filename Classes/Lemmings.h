#pragma once
#include "cocos2d.h"

USING_NS_CC;

class Lemmings : public cocos2d::Sprite
{
public:
	Lemmings(Vec2 pos);
	void move();
	void ChangeDirection();

private:
	int direction;
	float speed;
};