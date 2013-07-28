#include "HealthBar.h"

HealthBar::~HealthBar() {
}

bool HealthBar::init(float healthLevel) {
	if ( !Layer::init() )
    {
        return false;
    }

	_healthLevel = healthLevel;
	this->setContentSize(CCSizeMake(256,40));
	this->setPosition(25, 720);

	Sprite* gaugeSprite = Sprite::createWithSpriteFrameName("lifebar.png");
	gaugeSprite->setAnchorPoint(ccp(0, 0));
	gaugeSprite->setPosition(ccp(0, 0));

	/*
	LayerColor* bgBar = LayerColor::create(ccc4(0, 0, 0, 255));
	bgBar->setPosition(0, 0);
	bgBar->setContentSize(CCSizeMake(256, 40));
	*/

	_bar = LayerColor::create(ccc4(0, 255, 0, 255));
	_bar->setPosition(5, 5);
	_bar->setContentSize(CCSizeMake(250, 34));

	Sprite* healthIcon = Sprite::createWithSpriteFrameName("donut.png");
	healthIcon->setPosition(ccp(0, this->getContentSize().height / 2));
	healthIcon->setOpacity(240);
	
	
	this->addChild(_bar);
	this->addChild(gaugeSprite);
	this->addChild(healthIcon);

	return true;
}


void HealthBar::setHealthLevel(float health) {
	_healthLevel = health;
}

void HealthBar::update(float dt) {
	int bgbarMaxWidth = 250;
	_bar->setContentSize(CCSizeMake(bgbarMaxWidth * (_healthLevel / 100), 34));



}