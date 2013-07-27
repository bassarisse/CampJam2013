
#include "Enemy.h"

Enemy::~Enemy() {
    
}

void Enemy::addFixtures() {
	
}

bool Enemy::init(b2World *world, Dictionary *properties, Player *ref) {
    
    //_node = Sprite::createWithSpriteFrameName("right1.png");
	_playerReference = ref;

    if (!GameObject::init(world, properties))
        return false;
    
    return true;
}

void Enemy::update(float dt) {
    
    GameObject::update(dt);
    
}

void Enemy::handleCollisions()  {
	//Override this shit!
}