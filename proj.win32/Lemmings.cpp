#include "Lemmings.h"
#define RIGHT 0
#define LEFT 1
#define DEFAULT_SPEED 1


Lemmings::Lemmings(Vec2 pos)
{
	this->setTexture("HelloWorld.png");
	this->setPosition(pos);
	this->direction = RIGHT;
	this->speed = DEFAULT_SPEED;
}

void Lemmings::move()
{
	// todo : detect collision

	// todo : detect platform under the lemmings

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

void Lemmings::changeDirection()
{
	this->direction = ~this->direction;
}


