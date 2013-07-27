#include "Woman.h"

Woman::~Woman() {
	
}


void Woman::addFixtures() {
    
    float width = _node->getContentSize().width * 0.32f;
    float height = _node->getContentSize().height * 0.2f;
    //this->addCircularFixture(width / 2);
    this->addRectangularFixture(0, -height * 2, width, height);

}

bool Woman::init(b2World *world, Dictionary *properties, Player *ref) {
	
	//FIXME
	_node = Sprite::createWithSpriteFrameName("woman_down.png");
    _spriteFrameName = "woman";
    
	_damageFactor = 0.3f;
	_speedFactor = 1.0f;
    
	this->setType(GameObjectTypeWoman);
	
	if (!Enemy::init(world, properties, ref))
        return false;
    
	_speedFactor = -2.4f;
    
    return true;
}