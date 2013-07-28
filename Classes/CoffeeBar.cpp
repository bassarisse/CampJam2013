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

	LayerColor* bgBar = LayerColor::create(ccc4(0, 0, 0, 255));
	bgBar->setPosition(80, 670);
	bgBar->setContentSize(CCSizeMake(256, 40));

	_bar = LayerColor::create(ccc4(94, 49, 19, 255));
	_bar->setPosition(83, 673);
	_bar->setContentSize(CCSizeMake(250, 34));

	LayerColor *coffeeThreshold = LayerColor::create(ccc4(120,120,120,255));

	coffeeThreshold->setPosition(
		_bar->getPosition().x + (_bar->getContentSize().width * (kCoffeeThreshold / 100 ) ), 673);

	coffeeThreshold->setContentSize(CCSizeMake(3, 34));

	this->addChild(bgBar);
	this->addChild(_bar);
	this->addChild(coffeeThreshold);
	return true;
}


void CoffeeBar::setCoffeeLevel(float coff) {
	_coffeeLevel = coff;
}

void CoffeeBar::update(float dt) {
	int bgbarMaxWidth = 250;
	_bar->setContentSize(CCSizeMake(bgbarMaxWidth * (_coffeeLevel / 100), 34));



}