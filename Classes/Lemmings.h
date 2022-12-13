#pragma once
#include "cocos2d.h"

USING_NS_CC;

class Lemmings : public cocos2d::Sprite
{
public:
	Lemmings(Vector<SpriteFrame*> frame);
	void move();
	void ChangeDirection();
	void setAnimation(Vector<SpriteFrame*> frame);

private:
	bool direction;
	float speed;
};