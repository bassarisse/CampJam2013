#include "Man.h"

#include "SimpleAudioEngine.h"

void Man::addFixtures() {
    
    float width = _node->getContentSize().width * 0.32f;
    float height = _node->getContentSize().height * 0.2f;
    
    this->addCircularFixture(0, -height * 2, width / 2);
    //this->addRectangularFixture(0, -height * 2, width, height);

} 

bool Man::init(b2World *world, Dictionary *properties, Player *ref) {
	
	//FIXME
	_node = Sprite::createWithSpriteFrameName("man_down.png");
    _spriteFrameName = "man";
    
    _damageFactor = 1.0f;

	this->setType(GameObjectTypeMan);
	
	if (!Enemy::init(world, properties, ref))
        return false;
    
	_speedFactor = -3.4f;
    
    return true;
}

void Man::die() {
    CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("death_man.wav");
    Enemy::die();
}

void Man::updatePosition(Point position) {
    position.y += 10;
    _node->setPosition(position);
}