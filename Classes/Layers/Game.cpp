#include "Game.h"

USING_NS_CC;

bool Game::init()
{
	if (!Layer::init()) return false;

	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

    comboLabel1 = Label::createWithTTF("1", "fonts/arial.ttf", visibleSize.height * 0.1);
    comboLabel1->setColor(Color3B::WHITE);
    comboLabel1->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));
    comboLabel1->setTag(666);
    addChild(comboLabel1, 90000);

    return true;
}
