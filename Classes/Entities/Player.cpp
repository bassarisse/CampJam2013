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

    if (!GameObject::init(world, properties))
        return false;
    
    this->setType(GameObjectTypePlayer);
    
    return true;
}

void Player::update(float dt) {
    
    CCLog("_coffee: %f", _coffee);
    CCLog("_life: %f", _life);
    
    GameObject::update(dt);
    
    float affectValue = dt * kCoffeeDamage;
    
    _coffee -= affectValue;
    if (_coffee < 0) _coffee = 0;
    
    if (_coffee > kCoffeeThreshold) {
        _life -= affectValue;
    }
    
    if (this->getState() == GameObjectStateWalking && !_node->getActionByTag(kWalkActionTag)) {
        
        SpriteFrameCache *spriteCache = SpriteFrameCache::sharedSpriteFrameCache();
        
        const char *frameName = getDirectionName(_lastDirection);
        
        Animation *anim = Animation::create();
        anim->setDelayPerUnit(0.2f);
        anim->setRestoreOriginalFrame(true);
        
        anim->addSpriteFrame(spriteCache->spriteFrameByName(String::createWithFormat("%s2.png", frameName)->getCString()));
        anim->addSpriteFrame(spriteCache->spriteFrameByName(String::createWithFormat("%s1.png", frameName)->getCString()));
        anim->addSpriteFrame(spriteCache->spriteFrameByName(String::createWithFormat("%s3.png", frameName)->getCString()));
        anim->addSpriteFrame(spriteCache->spriteFrameByName(String::createWithFormat("%s1.png", frameName)->getCString()));
        
        Action *repeatAction = RepeatForever::create(Animate::create(anim));
        repeatAction->setTag(kWalkActionTag);
        
        _node->stopAllActions();
        _node->runAction(repeatAction);
        
    } else if (this->getState() == GameObjectStateStanding) {
        
        _node->stopAllActions();
        
    }
    
}

float Player::getSpeed() {
    CCLog("speed: %f", _speedFactor + _coffee * kCoffeePower);
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