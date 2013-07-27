#include "Water.h"

Water::~Water() {
	
}

void Water::addFixtures() {
	float width = _node->getContentSize().width * 0.6f;
    float height = _node->getContentSize().height * 0.6f;
    this->addRectangularFixture(width, height);
}

bool Water::init(b2World *world, Dictionary *properties) {
    
	//FIXME
    _node = Sprite::createWithSpriteFrameName("man_down_right2.png");
	_node->setScale(0.1f);
	
	this->setType(GameObjectTypeWater);
    if (!GameObject::init(world, properties))
        return false;
    
    return true;
}

void Water::update(float dt) {
	GameObject::update(dt);
}