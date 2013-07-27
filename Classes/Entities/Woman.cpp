#include "Woman.h"

Woman::~Woman() {
	
}


void Woman::addFixtures() {
	
	float width = _node->getContentSize().width;// * 0.75f;
    float height = _node->getContentSize().height;// * 0.8f;
    //this->addCircularFixture(width / 2);
    this->addRectangularFixture(width, height);

}

bool Woman::init(b2World *world, Dictionary *properties) {
	
	//FIXME
	_node = Sprite::createWithSpriteFrameName("woman.png");

	damageFactor = 0.3;
	speedFactor = 1.0;
	

	if (!Enemy::init(world, properties))
        return false;
    
    return true;
}

void Woman::update(float dt) {
	Enemy::update(dt);
}

void Woman::handleCollisions() {
	
	
}