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
	bgBar->setPosition(970, 400);
	bgBar->setContentSize(CCSizeMake(46, 256));

	_bar = LayerColor::create(ccc4(94, 49, 19, 255));
	_bar->setPosition(973, 400);
	_bar->setContentSize(CCSizeMake(40, 250));

	LayerColor *coffeeThreshold = LayerColor::create(ccc4(0,0,0,255));
	coffeeThreshold->setPosition(973, 
		_bar->getPosition().y + (_bar->getContentSize().height * (kCoffeeThreshold / 100 ) ));

	coffeeThreshold->setContentSize(CCSizeMake(40, 6));

	this->addChild(bgBar);
	this->addChild(_bar);
	this->addChild(coffeeThreshold);
	return true;
}


void CoffeeBar::setCoffeeLevel(float coff) {
	_coffeeLevel = coff;
}

void CoffeeBar::update(float dt) {
	int bgbarMaxHeight = 250;
	_bar->setContentSize(CCSizeMake(40, bgbarMaxHeight * (_coffeeLevel / 100)));



}