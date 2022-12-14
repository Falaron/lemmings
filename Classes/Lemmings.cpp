#include "Lemmings.h"
#include "MapLoader.h"
#define RIGHT false
#define LEFT true
#define DEFAULT_SPEED 15.0f

#include <iostream>


Lemmings::Lemmings()
{
	this->setPosition(*MapLoader::GetSpawnPoint());
	this->_direction = RIGHT;
	this->_speed = DEFAULT_SPEED;
	this->_state = SPAWNING;
	this->updateAnimation();

	PhysicsBody* box = PhysicsBody::createBox(this->getContentSize(), PhysicsMaterial(0.2f,0,0));
	box->setGravityEnable(true);
	box->setDynamic(true);
	box->setRotationEnable(false);

	this->addComponent(box);
}

void Lemmings::move()
{
	const auto physicsBody = this->getPhysicsBody();
	const auto velocity = physicsBody->getVelocity();


	// detect if the lemmings is falling
	if ((int)velocity.y == 0)
	{
		// detect if the lemmgings is moving will is in the ground
		if (this->_state == MOVING) {
			if (((int)velocity.x * 100) / 100 == 0) this->ChangeDirection();
		}
		else { 
			this->_state = MOVING;
			this->updateAnimation();
		}

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
		if (this->_state != FALLING) { this->_state = FALLING; }
		this->updateAnimation();
		physicsBody->setVelocity(Vec2(0, velocity.y));
	}
}

void Lemmings::ChangeDirection()
{
	this->_direction = !_direction;
	this->setFlippedX(_direction);
}

void Lemmings::updateAnimation()
{
	switch (this->_state)
	{
	case SPAWNING:
		frames = GetAnimation("walk-%04d.png", 9);
		this->setSpriteFrame(frames.front());
		this->runAction(Animate::create(Animation::createWithSpriteFrames(frames, 1.0f / 9)));
		CCLOG("SPAWNING");
		
		break;

	case FALLING:
		frames = GetAnimation("fall-%04d.png", 5);
		this->setSpriteFrame(frames.front());
		this->runAction(Animate::create(Animation::createWithSpriteFrames(frames, 1.0f / 5)));	
		CCLOG("FALLING");
		break;

	case MOVING:
		frames = GetAnimation("walk-%04d.png", 9);
		this->setSpriteFrame(frames.front());
		this->runAction(Animate::create(Animation::createWithSpriteFrames(frames, 1.0f / 9)));
		CCLOG("MOVING");
		break;

	default:
		break;
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

