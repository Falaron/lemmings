#pragma once
#include "cocos2d.h"
#include "PhysicsShapeCache.h"

enum state {
	SPAWNING,
	FALLING,
	MOVING,
};

USING_NS_CC;

class Lemmings : public cocos2d::Sprite
{
public:
	Lemmings();
	void move();
	void ChangeDirection();
	void updateAnimation();

private:
	cocos2d::Vector<cocos2d::SpriteFrame*> GetAnimation(const char* format, int count);
	bool _direction;
	float _speed;
	state _state;
	cocos2d::Vector<cocos2d::SpriteFrame*> frames;
	cocos2d::Animation* animation;
};