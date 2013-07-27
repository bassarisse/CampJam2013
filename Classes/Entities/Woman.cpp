#include "Woman.h"

Woman::~Woman() {
	
}


void Woman::addFixtures() {
	
	float width = _node->getContentSize().width;// * 0.75f;
    float height = _node->getContentSize().height;// * 0.8f;
    //this->addCircularFixture(width / 2);
    this->addRectangularFixture(width, height);

}

bool Woman::init(b2World *world, Dictionary *properties, Player *ref) {
	
	//FIXME
	_node = Sprite::createWithSpriteFrameName("woman.png");
    _spriteFrameName = "woman";
    
	_damageFactor = 0.3f;
	_speedFactor = 1.0f;
	

	if (!Enemy::init(world, properties, ref))
        return false;
    
    return true;
}

void Woman::update(float dt) {
	Enemy::update(dt);
}

void Woman::handleCollisions() {
	
	
}