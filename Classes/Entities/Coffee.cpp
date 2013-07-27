#include "Coffee.h"

Coffee::~Coffee() {
	
}

void Coffee::addFixtures() {
	float width = _node->getContentSize().width * 0.6f;
    float height = _node->getContentSize().height * 0.6f;
    this->addRectangularFixture(width, height);
}

bool Coffee::init(b2World *world, Dictionary *properties) {
    
    _node = Sprite::createWithSpriteFrameName("coffee.png");
    _isSensor = true;
	
	this->setType(GameObjectTypeCoffee);

    if (!GameObject::init(world, properties))
        return false;
    
    return true;
}