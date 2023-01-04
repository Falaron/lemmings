#include "Lemmings.h"
#include "MapLoader.h"
#define RIGHT false
#define LEFT true
#define UP false
#define DOWN true
#define DEFAULT_SPEED 13.0f

#include <iostream>


Lemmings::Lemmings()
{
	// setup private var
	this->setPosition(*MapLoader::GetSpawnPoint());
	this->_horizontalDirection = RIGHT;
	this->_verticalDirection = UP;
	this->_speed = DEFAULT_SPEED;
	this->_currentAnimation = SPAWNING;
	this->_state = SPAWNING;
	this->setScale(1);

	// create a temp sprite to setup the physic box ( in game animation is manage in UpdateAnimation() )
	auto frames = GetAnimation("walk-%04d.png", 9);
	this->setSpriteFrame(frames.front());


	//create Physic body and setup basics parameters
	box = PhysicsBody::createBox(this->getContentSize(), PhysicsMaterial(0, 0, 0));
	box->setGravityEnable(true);
	box->setGroup(-1);
	box->setGroup(1);
	box->setContactTestBitmask(0xFFFFFFFF);
	box->setDynamic(true);
	box->setRotationEnable(false);

	this->addComponent(box);
}

void Lemmings::Update()
{
	const auto physicsBody = this->getPhysicsBody();
	const auto velocity = physicsBody->getVelocity();

	if (this->_state == JUMPING) { this->Jump(); }

	else if (this->_state == PARACHUTING) { this->Parachute(); }

	else {

		// detect if the lemmings is falling
		if ((int)velocity.y == 0)
		{
			// detect if the lemmgings is moving will he's on the ground
			if (this->_state == MOVING) {
				if ((int)velocity.x == 0) this->ChangeDirection();
			}
			else { this->_state = MOVING; }

			//movement
			this->Move();
		}

		else
		{
			if (this->_state != FALLING) { this->_state = FALLING; }
			physicsBody->setVelocity(Vec2(0, velocity.y));
		}

		this->UpdateAnimation();
	}
	this->setVerticalDirection();
}

void Lemmings::ChangeDirection()
{
	this->_horizontalDirection = !_horizontalDirection;
	this->setFlippedX(_horizontalDirection);
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
			this->runAction(Animate::create(Animation::createWithSpriteFrames(frames, 1.0f / 5)));
			this->_currentAnimation = FALLING;

			break;

		case MOVING:
			frames = GetAnimation("walk-%04d.png", 9);
			this->setSpriteFrame(frames.front());
			this->runAction(RepeatForever::create(Animate::create(Animation::createWithSpriteFrames(frames, 1.0f / 9))));
			this->_currentAnimation = MOVING;

			break;

		case JUMPING:
			frames = GetAnimation("fall-%04d.png", 5);
			this->setSpriteFrame(frames.front());
			this->runAction(Animate::create(Animation::createWithSpriteFrames(frames, 1.0f / 5)));
			this->_currentAnimation = JUMPING;

			break;

		case PARACHUTING:
			frames = GetAnimation("parachute-%04d.png", 8);
			this->setSpriteFrame(frames.front());
			this->runAction(Animate::create(Animation::createWithSpriteFrames(frames, 1.0f / 5)));
			this->_currentAnimation = PARACHUTING;

			break;

		case DIGGING:
			frames = GetAnimation("digging-%04d.png", 8);
			this->setSpriteFrame(frames.front());
			this->runAction(RepeatForever::create(Animate::create(Animation::createWithSpriteFrames(frames, 1.0f / 8))));
			this->_currentAnimation = DIGGING;

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

void Lemmings::Move()
{
	float distance;
	if (this->_horizontalDirection)
	{
		distance = -this->_speed;
	}
	else
	{
		distance = this->_speed;
	}
	this->getPhysicsBody()->setVelocity(Vec2(distance, this->getPhysicsBody()->getVelocity().y));
}

void Lemmings::Jump()
{
	// check only if the state change
	if (this->_state != this->_currentAnimation) {

		auto jump = JumpBy::create(1.6f, Vec2(2.0f, 0.0f), 2.0f, 1);

		auto callbackChangeState = CallFunc::create([this]() {
			this->_state = MOVING;
			});

		auto seq = Sequence::create(jump, callbackChangeState, nullptr);
		this->runAction(seq);
	}
}

void Lemmings::Parachute()
{
	auto physicsBody = this->getPhysicsBody();
	auto velocity = physicsBody->getVelocity();

	// check only if the state change
	if (this->_state != this->_currentAnimation) 
	{
		physicsBody->setVelocity(Vec2(velocity.x, 50.0f));
	}
	else {
		if ((int)velocity.y == 0 && this->_verticalDirection == DOWN)
		{
			this->Move();
			this->_state = MOVING;
		}
		else
		{
			if (velocity.y < -8.0f) physicsBody->setVelocity(Vec2(velocity.x, -8.0f));
		}
	}

	physicsBody = this->getPhysicsBody();
	velocity = physicsBody->getVelocity();

	CCLOG("velocity end: %f . %f", velocity.x, velocity.y);
	this->UpdateAnimation();
}

void Lemmings::setVerticalDirection() {
	const auto velocityY = this->getPhysicsBody()->getVelocity().y;
	if (velocityY > 0) this->_verticalDirection = UP;
	else if (velocityY < 0) this->_verticalDirection = DOWN;
	
}

void Lemmings::Digging()
{
	auto physicsBody = this->getPhysicsBody();
	auto velocity = physicsBody->getVelocity();

	if (this->_state != this->_currentAnimation)
	{
		auto delay = DelayTime::create(1);
		auto destroyBlock = CallFunc::create([this]() 
			{
			
			}
		);


		auto callbackChangeState = CallFunc::create([this]() { this->_state = MOVING; });

		auto seq = Sequence::create(delay, destroyBlock, callbackChangeState, nullptr);
		this->runAction(seq);
	}
}