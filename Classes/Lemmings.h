#pragma once
#include "cocos2d.h"

enum state {
	SPAWNING,
	FALLING,
	MOVING,
};

USING_NS_CC;

class Lemmings : public cocos2d::Sprite
{
public:
	Lemmings(Vector<SpriteFrame*> frame);
	void move();
	void ChangeDirection();
	void setAnimation(Vector<SpriteFrame*> frame);

private:
	bool _direction;
	float _speed;
	state _state;
};