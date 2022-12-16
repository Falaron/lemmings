#pragma once
#include "cocos2d.h"
#include "PhysicsShapeCache.h"

enum state {
	SPAWNING,
	FALLING,
	MOVING,
	JUMPING,
	PARACHUTING,
};

USING_NS_CC;

class Lemmings : public cocos2d::Sprite
{
public:
	/// <summary> Spawn point define by the map (refer to MapLoader.h) / Create the physicalBody / Animation manage by UpdateAnimation() </summary>
	Lemmings();

	/// <summary> main loop for each lemmings. Mange collisions, actions and movements. </summary>
	void Update();

	/// <summary> change the direction of the lemmings </summary>
	void ChangeDirection();

	/// <summary> Manage Animations of the lemmings depend on which state he is </summary>
	void UpdateAnimation();

	/// <summary> Return true if the lemming is in the map </summary>
	bool isInMap();

	/// <summary> Move forward depend of the direction </summary>
	void Move();

	/// <summary> Jump action </summary>
	void Jump();

	/// <summary> Parachute action </summary>
	void Parachute();

private:
	cocos2d::Vector<cocos2d::SpriteFrame*> GetAnimation(const char* format, int count);
	void setVerticalDirection();

	bool _horizontalDirection;
	bool _verticalDirection;
	float _speed;
	state _state;
	state _currentAnimation;
};