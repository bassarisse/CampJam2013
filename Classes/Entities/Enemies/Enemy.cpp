
#include "Enemy.h"

Enemy::~Enemy() {
    
}

void Enemy::addFixtures() {
	
}

bool Enemy::init(b2World *world, Dictionary *properties, Player *ref) {
    
    //_node = Sprite::createWithSpriteFrameName("right1.png");
	_playerReference = ref;
    _drinkedCoffee = 0;

    if (!GameObject::init(world, properties))
        return false;
    
    return true;
}

void Enemy::handleMovement() {
	GameObject::handleMovement(this->getAngleForPoint(_playerReference->getNode()->getPosition()));
}

void Enemy::update(float dt) {
    
    GameObject::update(dt);
    
    this->executeWalkAnimation();
    
    int colorAdd = 255 - 60 * _drinkedCoffee;
    Sprite *thisSprite = (Sprite *)this->getNode();
    thisSprite->setColor(ccc3(255, colorAdd, colorAdd));
    
	if(_drinkedCoffee >= kEnemyDeathCoffeeNumber && _state != GameObjectStateDead)
        this->setState(GameObjectStateDead);
    
}

void Enemy::handleCollision(GameObject *gameObject)  {
    
    switch(gameObject->getType()) {
            
        case GameObjectTypeCoffee:
        case GameObjectTypePeaBerry:
            _speedFactor += 1.9f;
            _drinkedCoffee++;
            gameObject->setState(GameObjectStateDead);
            
            break;
            
        default:
            break;
    }
    
}