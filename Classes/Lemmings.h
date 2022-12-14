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
	/// <summary> Spawn point define by the map (refer to MapLoader.h) / Create the physicalBody / Animation manage by UpdateAnimation() </summary>
	Lemmings();

	/// <summary> check collisions and automatically move accordingly </summary>
	void Move();

	/// <summary> change the direction of the lemmings </summary>
	void ChangeDirection();

	/// <summary> Manage Animations of the lemmings depend on which state he is </summary>
	void UpdateAnimation();

private:
	cocos2d::Vector<cocos2d::SpriteFrame*> GetAnimation(const char* format, int count);
	bool _direction;
	float _speed;
	state _state;
	state _currentAnimation;
};