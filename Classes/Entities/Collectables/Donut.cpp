#include "Donut.h"

Donut::~Donut() {
	
}

void Donut::addFixtures() {
	float width = _node->getContentSize().width * 0.6f;
    float height = _node->getContentSize().height * 0.6f;
    this->addRectangularFixture(width, height);
}

bool Donut::init(b2World *world, Dictionary *properties) {
    
    _node = Sprite::createWithSpriteFrameName("donut.png");
	
	this->setType(GameObjectTypeDonut);

    if (!GameObject::init(world, properties))
        return false;
    
    _isSensor = true;
    
    return true;
}