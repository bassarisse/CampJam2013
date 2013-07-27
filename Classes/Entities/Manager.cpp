#include "Manager.h"

Manager::~Manager() {
	
}


void Manager::addFixtures() {
    
    float width = _node->getContentSize().width * 0.32f;
    float height = _node->getContentSize().height * 0.2f;
    //this->addCircularFixture(width / 2);
    this->addRectangularFixture(0, -height * 2, width, height);

}

bool Manager::init(b2World *world, Dictionary *properties, Player *ref) {
	
	//FIXME
	_node = Sprite::createWithSpriteFrameName("manager_down.png");
    _spriteFrameName = "manager";
    
	_damageFactor = 0.3f;
	_speedFactor = 1.0f;
    
	this->setType(GameObjectTypeManager);
	
	if (!Enemy::init(world, properties, ref))
        return false;
    
	_speedFactor = -4.5f;
    
    return true;
}