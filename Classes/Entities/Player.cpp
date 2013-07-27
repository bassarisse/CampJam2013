//
//  Player.cpp
//  PlatformerTest
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

void Player::handleCollisions() {

	for(std::vector<GameObject*>::size_type i = 0; i < _contacts.size(); i++)
	{
		GameObject* collisionObject = _contacts[i];
		switch(collisionObject->getType()) {
            case GameObjectTypeCoffee:
                _speedFactor += 0.05f;
                
                break;
            default:
                break;
		}
		
	}
    

}

