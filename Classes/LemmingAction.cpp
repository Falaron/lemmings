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

	_actionCountText = Label::createWithSystemFont(std::to_string(actionCount), "fonts/arial.ttf", 15);
	_actionCountText->setAnchorPoint(Vec2(0.5, 0.5));
	_actionCountText->setPosition(5, 30);
	addChild(_actionCountText);

	//TODO: move counter small
}
