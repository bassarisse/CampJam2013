#include "Coffee.h"

Coffee::~Coffee() {
	
}

void Coffee::addFixtures() {
	float width = _node->getContentSize().width * 0.6f;
    float height = _node->getContentSize().height * 0.6f;
    this->addRectangularFixture(width, height);
}

bool Coffee::init(b2World *world, Dictionary *properties) {
    //FIXME
    _node = Sprite::createWithSpriteFrameName("man_down_right2.png");
	_node->setScale(0.2f);
	
	this->setType(GameObjectTypeCoffee);

    if (!GameObject::init(world, properties))
        return false;
    
    return true;
}

void Coffee::update(float dt) {
	GameObject::update(dt);
}