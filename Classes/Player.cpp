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
    
    _node = Sprite::createWithSpriteFrameName("right1.png");
    _life = 100.0f;
    _coffee = 100.0f;

    if (!GameObject::init(world, properties))
        return false;
    
    this->setType(GameObjectTypePlayer);
    
    return true;
}

void Player::update(float dt) {
    
    GameObject::update(dt);
    
}