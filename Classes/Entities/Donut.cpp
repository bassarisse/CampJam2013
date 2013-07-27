#include "Donut.h"

Donut::~Donut() {
	
}

void Donut::addFixtures() {
	float width = _node->getContentSize().width * 0.6f;
    float height = _node->getContentSize().height * 0.6f;
    this->addRectangularFixture(width, height);
}

bool Donut::init(b2World *world, Dictionary *properties) {
    //FIXME
    _node = Sprite::createWithSpriteFrameName("man_down.png");
	_node->setScale(0.3f);
	
	this->setType(GameObjectTypeDonut);

    if (!GameObject::init(world, properties))
        return false;
    
    return true;
}

void Donut::update(float dt) {
	GameObject::update(dt);
}