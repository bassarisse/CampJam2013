#include "HealthBar.h"

bool HealthBar::init(float healthLevel) {
	if ( !Layer::init() )
    {
        return false;
    }

	_healthLevel = healthLevel;
	this->setContentSize(CCSizeMake(256,40));
	this->setPosition(25, 720);

	_gaugeSprite = Sprite::createWithSpriteFrameName("lifebar.png");
	_gaugeSprite->setAnchorPoint(ccp(0, 0));
	_gaugeSprite->setPosition(ccp(0, 0));

	_bar = LayerColor::create(ccc4(30, 230, 30, 255));
	_bar->setPosition(5, 5);
    
    this->update(0);

	Sprite* healthIcon = Sprite::createWithSpriteFrameName("donut.png");
	healthIcon->setPosition(ccp(0, this->getContentSize().height / 2));
	healthIcon->setOpacity(240);
	
	this->addChild(_bar);
	this->addChild(_gaugeSprite);
	this->addChild(healthIcon);

	return true;
}


void HealthBar::setHealthLevel(float health) {
	_healthLevel = health;
}

void HealthBar::update(float dt) {
	int bgbarMaxWidth = _gaugeSprite->getContentSize().width - 7;
	_bar->setContentSize(CCSizeMake(bgbarMaxWidth * (_healthLevel / 100), 36));
}

void HealthBar::blinkBar() {
	Blink* blink = Blink::create(0.3f, 2);
	this->stopAllActions();
	this->runAction(Sequence::create(Show::create(), blink, NULL));
}