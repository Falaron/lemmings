#include "LemmingAction.h"
#include "Layers/HUDLayer.h"

#define HUD_LAYER_NAME "HUDLayer"

const float ACTION_SPRITE_SCALE_FACTOR = 1.25f;

USING_NS_CC;

void LemmingAction::Initialize(int index, LemmingActionName action, int actionCount)
{
	_action = action;
	_actionIndex = index;
	_actionCount = actionCount;

	setScale(ACTION_SPRITE_SCALE_FACTOR);
	setPositionX(40 + (index * getContentSize().width * getScale()));
	setAnchorPoint(Vec2(0, 0));

	_actionCountText = Label::createWithSystemFont(std::to_string(actionCount), "fonts/arial.ttf", 9);
	_actionCountText->setPositionX(16 * ACTION_SPRITE_SCALE_FACTOR);
	_actionCountText->setPositionY(_actionCountText->getPositionX());
	addChild(_actionCountText);

	//TODO: move counter small
}
