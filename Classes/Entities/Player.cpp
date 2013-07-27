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
    
    float width = _node->getContentSize().width * 0.75f;
    float height = _node->getContentSize().height * 0.8f;
    //this->addCircularFixture(width / 2);
    this->addRectangularFixture(width, height);
    
}

bool Player::init(b2World *world, Dictionary *properties) {
    
    _node = Sprite::createWithSpriteFrameName("down1.png");
    _life = 100.0f;
    _coffee = 100.0f;
    _speedFactor = 0.0f;

    if (!GameObject::init(world, properties))
        return false;
    
    this->setType(GameObjectTypePlayer);
    
    return true;
}

void Player::update(float dt) {
    
    GameObject::update(dt);
    
}

void Player::handleCollisions() {
    
	for(std::vector<GameObject*>::size_type i = 0; i <= _contacts.size(); i++)
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