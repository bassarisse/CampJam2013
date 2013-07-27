//
//  Player.cpp
//  CampJam
//
//  Created by Bruno Assarisse on 23/07/13.
//
//

#include "Player.h"

Player::~Player() {
    
}

void Player::addFixtures() {
    
    float width = _node->getContentSize().width * 0.32f;
    float height = _node->getContentSize().height * 0.2f;
    //this->addCircularFixture(width / 2);
    this->addRectangularFixture(0, -height * 2, width, height);
    
}

bool Player::init(b2World *world, Dictionary *properties) {
    
    _node = Sprite::createWithSpriteFrameName("stag_down.png");
    _life = 100.0f;
    _coffee = 100.0f;
    _spriteFrameName = "stag";

    if (!GameObject::init(world, properties))
        return false;
    
    this->setType(GameObjectTypePlayer);
    
    return true;
}

void Player::update(float dt) {
  
    GameObject::update(dt);
    
    float affectValue = dt * kCoffeeDamage;
    
    _peaBerryTime -= dt;
    
    if (_peaBerryTime < 0) {
        _peaBerryTime = 0;
        if (_isUnderPeaBerryEffect) {
            _speedFactor -= kPeaBerrySpeedFactor;
            _isUnderPeaBerryEffect = false;
        }
    }
    
    _coffee -= affectValue;
    if (_coffee < 0) _coffee = 0;
    
    if (_coffee > kCoffeeThreshold) {
        _life -= affectValue;
    }
    
    this->executeWalkAnimation();
    
}

float Player::getSpeed() {
    return _speedFactor + _coffee * kCoffeePower;
}

void Player::handleCollision(GameObject *gameObject) {
    
    switch(gameObject->getType()) {
            
        case GameObjectTypeCoffee:
            _coffee += kCoffeeLevelAdd;
            if (_coffee > 100.0f)
                _coffee = 100.0f;
            gameObject->setState(GameObjectStateDead);
            
            break;
            
        case GameObjectTypePeaBerry:
            _speedFactor += kPeaBerrySpeedFactor;
            _isUnderPeaBerryEffect = true;
            _peaBerryTime = kPeaBerryTime;
            gameObject->setState(GameObjectStateDead);
            
            break;
            
        case GameObjectTypeWater:
            _coffee -= kDonutEffectAmout;
            if (_coffee < 0.0f)
                _coffee = 0.0f;
            gameObject->setState(GameObjectStateDead);
            
            break;
            
        case GameObjectTypeDonut:
            _life += kDonutEffectAmout;
            if (_life > 100.0f)
                _life = 100.0f;
            gameObject->setState(GameObjectStateDead);
            
            break;
            
        default:
            break;
    }
    

}

