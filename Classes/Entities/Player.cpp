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
    
    _node = Sprite::createWithSpriteFrameName("stag_down_right.png");
    _life = 100.0f;
    _coffee = 100.0f;

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
    
    if (this->getState() == GameObjectStateWalking && !_node->getActionByTag(kWalkActionTag)) {
        
        SpriteFrameCache *spriteCache = SpriteFrameCache::sharedSpriteFrameCache();
        
        const char *frameNameHorizontal = getDirectionName(_lastHorizontalDirection);
        const char *frameNameVertical = getDirectionName(_lastVerticalDirection);
        
        Animation *anim = Animation::create();
        anim->setDelayPerUnit(0.2f);
        anim->setRestoreOriginalFrame(true);
        
        anim->addSpriteFrame(spriteCache->spriteFrameByName(String::createWithFormat("stag_%s_%s1.png", frameNameVertical, frameNameHorizontal)->getCString()));
        anim->addSpriteFrame(spriteCache->spriteFrameByName(String::createWithFormat("stag_%s_%s2.png", frameNameVertical, frameNameHorizontal)->getCString()));
        
        Action *repeatAction = RepeatForever::create(Animate::create(anim));
        repeatAction->setTag(kWalkActionTag);
        
        _node->stopAllActions();
        _node->runAction(repeatAction);
        
    } else if (this->getState() == GameObjectStateStanding) {
        
        _node->stopAllActions();
        
    }
    
}

float Player::getSpeed() {
    return _speedFactor + _coffee * kCoffeePower;
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

b2Vec2 Player::getPosition() {
	return _body->GetPosition();
}