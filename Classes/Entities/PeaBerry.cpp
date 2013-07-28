#include "Peaberry.h"

Peaberry::~Peaberry() {
	
}

void Peaberry::addFixtures() {
	float width = _node->getContentSize().width * 0.6f;
    float height = _node->getContentSize().height * 0.6f;
    this->addRectangularFixture(width, height);
}

bool Peaberry::init(b2World *world, Dictionary *properties) {
    
	_node = Sprite::createWithSpriteFrameName("special_coffee.png");
    _isSensor = true;
    
	this->setType(GameObjectTypePeaBerry);

    if (!GameObject::init(world, properties))
        return false;
    
    return true;
}