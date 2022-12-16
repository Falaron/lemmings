#include "Lemmings.h"
#include "MapLoader.h"
#define RIGHT false
#define LEFT true
#define DEFAULT_SPEED 15.0f

#include <iostream>


Lemmings::Lemmings()
{
	// setup private var
	this->setPosition(*MapLoader::GetSpawnPoint());
	this->_direction = RIGHT;
	this->_speed = DEFAULT_SPEED;
	this->_currentAnimation = SPAWNING;
	this->_state = SPAWNING;
	this->setScale(1);

	// create a temp sprite to create the physic box ( in game animation is manage in UpdateAnimation()
	auto frames = GetAnimation("walk-%04d.png", 9);
	this->setSpriteFrame(frames.front());


	//create Physic body and setup basics parameters
	box = PhysicsBody::createBox(this->getContentSize(), PhysicsMaterial(0.2f,0,0));
	box->setGravityEnable(true);
	box->setGroup(-1);
	box->setGroup(1);
	box->setContactTestBitmask(0xFFFFFFFF);
	box->setDynamic(true);
	box->setRotationEnable(false);

	this->addComponent(box);
}

void Lemmings::Move()
{
	const auto physicsBody = this->getPhysicsBody();
	const auto velocity = physicsBody->getVelocity();


	// detect if the lemmings is falling
	if ((int)velocity.y == 0)
	{
		// detect if the lemmgings is moving will he's on the ground
		if (this->_state == MOVING) {
			if (((int)velocity.x * 100) / 100 == 0) this->ChangeDirection();
		}
		else { 
			this->_state = MOVING;
			this->UpdateAnimation();
		}

		//movement
		float distance;
		if (this->_direction)
		{
			distance = -this->_speed;
		}
		else
		{
			distance = this->_speed;
		}
		physicsBody->setVelocity(Vec2(distance, velocity.y));
	}
	else 
	{
		if (this->_state != FALLING) { 
			this->_state = FALLING; 
			this->UpdateAnimation();
		}
		physicsBody->setVelocity(Vec2(0, velocity.y));
	}
}

void Lemmings::ChangeDirection()
{
	this->_direction = !_direction;
	this->setFlippedX(_direction);
}

void Lemmings::UpdateAnimation()
{

	cocos2d::Vector<cocos2d::SpriteFrame*> frames;

	// check only if the state change
	if (this->_state != this->_currentAnimation) {
		this->stopAllActions();
		switch (this->_state)
		{
		case SPAWNING:
			frames = GetAnimation("walk-%04d.png", 9);
			this->setSpriteFrame(frames.front());
			this->runAction(RepeatForever::create(Animate::create(Animation::createWithSpriteFrames(frames, 1.0f / 9))));
			this->_currentAnimation = SPAWNING;

			break;

		case FALLING:
			frames = GetAnimation("fall-%04d.png", 5);
			this->setSpriteFrame(frames.front());
			this->runAction(RepeatForever::create(Animate::create(Animation::createWithSpriteFrames(frames, 1.0f / 5))));
			this->_currentAnimation = FALLING;

			break;

		case MOVING:
			frames = GetAnimation("walk-%04d.png", 9);
			this->setSpriteFrame(frames.front());
			this->runAction(RepeatForever::create(Animate::create(Animation::createWithSpriteFrames(frames, 1.0f / 9))));
			this->_currentAnimation = MOVING;

			break;

		default:
			break;

		}
	}
}

cocos2d::Vector<cocos2d::SpriteFrame*> Lemmings::GetAnimation(const char* format, int count)
{
	auto spritecache = SpriteFrameCache::getInstance();
	Vector<SpriteFrame*> animFrames;
	char str[100];
	for (int i = 1; i <= count; i++)
	{
		sprintf(str, format, i);
		animFrames.pushBack(spritecache->getSpriteFrameByName(str));
	}
	return animFrames;
}

bool Lemmings::isInMap()
{
	float y = this->getPositionY();
	if  (y < 0) {
		return false;
	}
	else return true;
}