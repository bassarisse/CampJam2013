#include "CoffeeBar.h"
#include "Common.h"

CoffeeBar::~CoffeeBar() {
}

bool CoffeeBar::init(float coffeeLevel) {
	if ( !Layer::init() )
    {
        return false;
    }

	_coffeeLevel = coffeeLevel;
	this->setContentSize(CCSizeMake(256,40));
	this->setPosition(25, 685);

	_gaugeSprite = Sprite::createWithSpriteFrameName("coffeebar.png");
	_gaugeSprite->setAnchorPoint(ccp(0, 0));
	_gaugeSprite->setPosition(ccp(0, 0));

	/*
	LayerColor* bgBar = LayerColor::create(ccc4(0, 0, 0, 255));
	bgBar->setPosition(0, 0);
	bgBar->setContentSize(CCSizeMake(256, 40));
	*/

	_bar = LayerColor::create(ccc4(12, 12, 12, 255));
	_bar->setPosition(5, 3);
	_bar->setContentSize(CCSizeMake(_gaugeSprite->getContentSize().width - 3, 25));

	
	LayerColor *coffeeThreshold = LayerColor::create(ccc4(255,0,0,255));

	coffeeThreshold->setPosition(
		(_bar->getContentSize().width * (kCoffeeThreshold / 100 ) ), 3);

	coffeeThreshold->setContentSize(CCSizeMake(3, 25));
	

	Sprite* coffeeIcon = Sprite::createWithSpriteFrameName("coffee.png");;
	coffeeIcon->setPosition(ccp(0, this->getContentSize().height / 2));
	coffeeIcon->setOpacity(240);

	this->addChild(_bar);
	this->addChild(coffeeThreshold);
	this->addChild(_gaugeSprite);
	this->addChild(coffeeIcon);
	return true;
}


void CoffeeBar::setCoffeeLevel(float coff) {
	_coffeeLevel = coff;
}

void CoffeeBar::update(float dt) {
	int bgbarMaxWidth = _gaugeSprite->getContentSize().width - 5;
	_bar->setContentSize(CCSizeMake(bgbarMaxWidth * (_coffeeLevel / 100), 25));

}

void CoffeeBar::blinkBar() {
	Blink* blink = Blink::create(0.3f, 2);
	this->stopAllActions();
	this->runAction(blink);
	
}

