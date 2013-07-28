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
	this->setPosition(80, 680);

	Sprite* gaugeSprite = Sprite::createWithSpriteFrameName("coffeebar.png");
	gaugeSprite->setAnchorPoint(ccp(0, 0));
	gaugeSprite->setPosition(ccp(-10, -10));

	/*
	LayerColor* bgBar = LayerColor::create(ccc4(0, 0, 0, 255));
	bgBar->setPosition(0, 0);
	bgBar->setContentSize(CCSizeMake(256, 40));
	*/

	_bar = LayerColor::create(ccc4(0, 255, 0, 255));
	_bar->setPosition(5, 3);
	_bar->setContentSize(CCSizeMake(250, 24));

	/*
	LayerColor *coffeeThreshold = LayerColor::create(ccc4(120,120,120,255));

	coffeeThreshold->setPosition(
		(this->getContentSize().width * (kCoffeeThreshold / 100 ) ), 3);

	coffeeThreshold->setContentSize(CCSizeMake(3, 34));
	*/

	Sprite* coffeeIcon = Sprite::createWithSpriteFrameName("coffee.png");;
	coffeeIcon->setPosition(ccp(0, this->getContentSize().height / 2));
	coffeeIcon->setOpacity(240);

	this->addChild(_bar);
	this->addChild(gaugeSprite);
	this->addChild(coffeeIcon);
	return true;
}


void CoffeeBar::setCoffeeLevel(float coff) {
	_coffeeLevel = coff;
}

void CoffeeBar::update(float dt) {
	int bgbarMaxWidth = 250;
	_bar->setContentSize(CCSizeMake(bgbarMaxWidth * (_coffeeLevel / 100), 34));



}