#include "HealthBar.h"

HealthBar::~HealthBar() {
}

bool HealthBar::init(float healthLevel) {
	if ( !Layer::init() )
    {
        return false;
    }

	_healthLevel = healthLevel;

	LayerColor* bgBar = LayerColor::create(ccc4(0, 0, 0, 255));
	bgBar->setPosition(80, 710);
	bgBar->setContentSize(CCSizeMake(256, 46));

	_bar = LayerColor::create(ccc4(255, 0, 0, 255));
	_bar->setPosition(83, 713);
	_bar->setContentSize(CCSizeMake(250, 40));

	

	this->addChild(bgBar);
	this->addChild(_bar);
	
	return true;
}


void HealthBar::setHealthLevel(float health) {
	_healthLevel = health;
}

void HealthBar::update(float dt) {
	int bgbarMaxWidth = 250;
	_bar->setContentSize(CCSizeMake(bgbarMaxWidth * (_healthLevel / 100), 40));



}