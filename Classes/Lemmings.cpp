#include "Lemmings.h"
#include "MapLoader.h"
#define RIGHT false
#define LEFT true
#define DEFAULT_SPEED 0.5f


Lemmings::Lemmings(Vector<SpriteFrame*> frame)
{
	this->setAnimation(frame);
	this->setPosition(*MapLoader::GetSpawnPoint());
	this->direction = RIGHT;
	this->speed = DEFAULT_SPEED;

	/*PhysicsBody* box = PhysicsBody::createEdgeBox(this->getContentSize(), PHYSICSBODY_MATERIAL_DEFAULT, 0.5f);
	box->setGravityEnable(true);
	box->setDynamic(true);
	this->setPhysicsBody(box);*/
}

void Lemmings::move()
{
	// todo : detect collision

	// todo : detect platform under the lemmings

	//tempTest {
	int posX = this->getPositionX();
	int posY = this->getPositionY();
	if (posX > 400) {
		this->ChangeDirection();
	}
	else if (posX < 0) {
		this->ChangeDirection();
	}
	// } end temp 


	float distance;
	if (this->direction) 
	{
		distance = -this->speed;
	}
	else
	{
		distance = this->speed;
	}
	this->setPosition(this->getPositionX() + distance, this->getPositionY());
}

void Lemmings::ChangeDirection()
{
	this->direction = !direction;
	this->setFlippedX(direction);
}

void Lemmings::setAnimation(Vector<SpriteFrame*> frame)
{
	this->setSpriteFrame(frame.front());
	auto animation = Animation::createWithSpriteFrames(frame, 1.0f / 9);
	this->runAction(RepeatForever::create(Animate::create(animation)));
}


