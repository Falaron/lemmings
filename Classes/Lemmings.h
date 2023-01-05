#pragma once

#include "cocos2d.h"
#include "PhysicsShapeCache.h"
#include "GameManager.h"

enum state {
	SPAWNING,
	FALLING,
	MOVING,
	JUMPING,
	PARACHUTING,
	DIGGING,
	BOMBING,
	HORIZONTALDIGGING,
	DEAD,
};

USING_NS_CC;

class Lemmings : public cocos2d::Sprite
{
public:

	void Initialize();
	CREATE_FUNC(Lemmings);

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

	/// <summary> Digging action </summary>
	void Digging();

	/// <summary> Digging action </summary>
	void HorizontalDigging();

	/// <summary> Bombing action </summary>
	void Bombing();

	state GetState() { return _state; };

private:
	cocos2d::Vector<cocos2d::SpriteFrame*> GetAnimation(const char* format, int count);
	void setVerticalDirection();

	bool _horizontalDirection;
	bool _verticalDirection;
	bool _thereIsGround;
	float _speed;
	state _state;
	state _currentAnimation;
	Node* _ground;
};