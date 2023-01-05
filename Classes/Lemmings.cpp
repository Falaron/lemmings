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
	this->_thereIsGround = false;
	this->setPosition(*MapLoader::GetSpawnPoint());
	this->_horizontalDirection = RIGHT;
	this->_verticalDirection = UP;
	this->_speed = DEFAULT_SPEED;
	this->_currentAnimation = SPAWNING;
	this->_state = BOMBING;
	this->setScale(1);

	// create a temp sprite to setup the physic box ( in game animation is manage in UpdateAnimation() )
	auto frames = GetAnimation("walk-%04d.png", 9);
	this->setSpriteFrame(frames.front());
	this->setName("lemming");


	//create Physic body and setup basics parameters
	box = PhysicsBody::createBox(this->getContentSize(), PhysicsMaterial(0, 0, 0));
	box->setGravityEnable(true);
	box->setGroup(-1);
	box->setContactTestBitmask(0xEEEEEEEE);
	box->setDynamic(true);
	box->setRotationEnable(false);
	box->setCollisionBitmask(1);

	this->addComponent(box);
}

void Lemmings::Update()
{
	const auto physicsBody = this->getPhysicsBody();
	const auto velocity = physicsBody->getVelocity();

	if (this->_state == JUMPING) { this->Jump(); }

	else if (this->_state == PARACHUTING) { this->Parachute(); }

	else if (this->_state == DIGGING) { this->Digging(); }

	else if (this->_state == BOMBING) { this->Bombing(); }

	else if (this->_state == DEAD) { }

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

		case BOMBING:
			frames = GetAnimation("bombing-%04d.png", 14);
			this->setSpriteFrame(frames.front());
			this->runAction(Sequence::create(DelayTime::create(3), Animate::create(Animation::createWithSpriteFrames(frames, 1.0f / 14)), nullptr));
			this->_currentAnimation = BOMBING;

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
	auto physicsBody = this->getPhysicsBody();
	auto velocity = physicsBody->getVelocity();

	// check only if the state change
	if (this->_state != this->_currentAnimation)
	{
		physicsBody->setVelocity(Vec2(30.0f , 70.0f));
	}
	else {
		if ((int)velocity.y == 0 && this->_verticalDirection == DOWN)
		{
			this->Move();
			this->_state = MOVING;
		}
	}

	this->UpdateAnimation();
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
		this->UpdateAnimation();
		auto delay = DelayTime::create(1);
		
		auto destroyBlock = CallFunc::create([this,velocity]() 
			{
				if (velocity.y == 0) {
					Vec2 position = *MapLoader::NormalizePosition(_ground->getPosition());
					MapLoader::DeleteTile(position);
				}
			}
		);


		auto callbackChangeState = CallFunc::create([this]() { this->_state = FALLING; });

		auto seq = Sequence::create(delay, destroyBlock, callbackChangeState, nullptr);
		this->runAction(seq);
	}
}

void Lemmings::SetGround(Node* ground, bool thereIsGround)
{
	_ground = ground;
	_thereIsGround = thereIsGround;
}

void Lemmings::Bombing()
{
	auto physicsBody = this->getPhysicsBody();
	auto velocity = physicsBody->getVelocity();
	int count = 3;
	auto countText = Label::createWithSystemFont(std::to_string(count),"fonts/arial.ttf",5);
	auto lemmingsPos = this->getPosition();
	countText->setPosition(Vec2(lemmingsPos.x+4, lemmingsPos.y+10));
	this->getParent()->addChild(countText,1);

	if (this->_state != this->_currentAnimation)
	{
		this->UpdateAnimation();
		auto delay = DelayTime::create(1);

		auto destroyBlock = CallFunc::create([this, velocity,lemmingsPos, countText]()
			{
				if (velocity.y == 0) {
					Vec2 position = *MapLoader::NormalizePosition(lemmingsPos);

					MapLoader::DeleteTile(Vec2(position.x, position.y + 1));
					MapLoader::DeleteTile(Vec2(position.x - 2, position.y + 1));
					MapLoader::DeleteTile(Vec2(position.x - 1, position.y + 1));
					MapLoader::DeleteTile(Vec2(position.x - 1, position.y + 2));
					MapLoader::DeleteTile(Vec2(position.x, position.y + 2));
					MapLoader::DeleteTile(Vec2(position.x, position.y + 3));
					MapLoader::DeleteTile(Vec2(position.x + 1, position.y + 2));
					MapLoader::DeleteTile(Vec2(position.x + 1, position.y + 1));
					MapLoader::DeleteTile(Vec2(position.x + 2, position.y + 1));
					countText->removeFromParentAndCleanup(true);

				}
			}
		);

		auto countDecrease = CallFunc::create([countText,count]()
			{
				countText->setString(std::to_string(count));
			}
		);


		auto callbackChangeState = CallFunc::create([this]() { this->_state = DEAD; });

		auto seq = Sequence::create(
									delay,
									count--,
									countDecrease,
									delay,
									count--,
									countDecrease,
									delay,
									count--,
									countDecrease,
									delay,
									destroyBlock,
									callbackChangeState,
									nullptr
									);
		this->runAction(seq);
	}
}