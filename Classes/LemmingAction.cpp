#include "LemmingAction.h"
#include "Layers/HUDLayer.h"

#define HUD_LAYER_NAME "HUDLayer"

const float ACTION_SPRITE_SCALE_FACTOR = 1.25f;

USING_NS_CC;

void LemmingAction::Initialize(int index, LemmingActionName action)
{
	_action = action;
	_actionIndex = index;

	setTag(5);
	setScale(ACTION_SPRITE_SCALE_FACTOR);
	setPositionX(40 + (index * getContentSize().width * getScale()));
	setAnchorPoint(Vec2(0, 0));

	auto box = PhysicsBody::createBox(getContentSize(), PhysicsMaterial(0, 0, 0));
	box->setDynamic(false);
	box->setGravityEnable(false);
	box->setRotationEnable(false);
	box->setCollisionBitmask(10);
	addComponent(box);
}
