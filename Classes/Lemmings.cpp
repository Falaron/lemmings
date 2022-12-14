#include "Lemmings.h"
#include "MapLoader.h"
#define RIGHT false
#define LEFT true
#define DEFAULT_SPEED 15.0f

#include <iostream>


Lemmings::Lemmings(Vector<SpriteFrame*> frame)
{
	this->setAnimation(frame);
	this->setPosition(*MapLoader::GetSpawnPoint());
	this->_direction = RIGHT;
	this->_speed = DEFAULT_SPEED;
	this->_state = SPAWNING;

	PhysicsBody* box = PhysicsBody::createBox(this->getContentSize(), PhysicsMaterial(0.2f,0,0));
	box->setGravityEnable(true);
	box->setDynamic(true);
	box->setRotationEnable(false);

	this->addComponent(box);
}

void Lemmings::move()
{
	//CCLOG("V�locit� : %f : %f", this->getPhysicsBody()->getVelocity().x,this->getPhysicsBody()->getVelocity().y);
	// detect if the lemmings is falling
	if ((((int)this->getPhysicsBody()->getVelocity().y * 100)) / 100 == 0)
	{
		// detect if the lemmgings is moving will is in the ground
		if (this->_state == MOVING) {
			if ((((int)this->getPhysicsBody()->getVelocity().x * 100)) / 100 == 0) this->ChangeDirection();
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
		this->getPhysicsBody()->setVelocity(Vec2(distance, this->getPhysicsBody()->getVelocity().y));

		if (this->_state != MOVING) this->_state = MOVING;
	}
	else 
	{
		this->_state = FALLING;
		this->getPhysicsBody()->setVelocity(Vec2(0, this->getPhysicsBody()->getVelocity().y));
	}
}

void Lemmings::ChangeDirection()
{
	this->_direction = !_direction;
	this->setFlippedX(_direction);
}

void Lemmings::setAnimation(Vector<SpriteFrame*> frame)
{
	this->setSpriteFrame(frame.front());
	auto animation = Animation::createWithSpriteFrames(frame, 1.0f / 9);
	this->runAction(RepeatForever::create(Animate::create(animation)));
}


