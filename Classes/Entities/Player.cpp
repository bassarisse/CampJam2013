//
//  Player.cpp
//  CampJam
//
//  Created by Bruno Assarisse on 23/07/13.
//
//

#include "Player.h"
#include "Enemies/Enemy.h"
#include "SimpleAudioEngine.h"
#include "../GamePlay.h"
#include "../Scenes/GameoverScene.h"

using namespace CocosDenshion;

Player::~Player() {
    
}

void Player::addFixtures() {
    
    float width = _node->getContentSize().width * 0.32f;
    float height = _node->getContentSize().height * 0.2f;
    //this->addCircularFixture(width / 2);
    this->addRectangularFixture(0, -height * 2, width, height);
    
}

bool Player::init(b2World *world, Dictionary *properties) {
    
	_score = 0;
    _node = Sprite::createWithSpriteFrameName("stag_down.png");
    _life = 100.0f;
    _coffee = 100.0f; // CHANGE IT!
    _spriteFrameName = "stag";

    if (!GameObject::init(world, properties))
        return false;
    
	

    return true;
}

void Player::update(float dt) {
  
    GameObject::update(dt);
    
    _damageTime -= dt;
    if (_damageTime < 0)
        _damageTime = 0;
    
    int colorAdd = 100 + 155 * ((kDamageTime - _damageTime) / kDamageTime);
    Sprite *thisSprite = (Sprite *)this->getNode();
    thisSprite->setColor(ccc3(255, colorAdd, colorAdd));
    
    _peaBerryTime -= dt;
    
    if (_peaBerryTime < 0) {
        _peaBerryTime = 0;
        if (_isUnderPeaBerryEffect) {
            _speedFactor -= kPeaBerrySpeedFactor;
            _isUnderPeaBerryEffect = false;
        }
    }
    
    float affectValue = dt * kCoffeeDamage;
    
    _coffee -= affectValue;
    if (_coffee < 0) _coffee = 0;
    
    if (_coffee > kCoffeeThreshold) {
        _life -= affectValue * (0.8f + _coffee / 100.0f);
    }
    
    if (_life < 0) {
		SimpleAudioEngine::sharedEngine()->playEffect("wilhem.wav");
		Scene* over = GameoverScene::scene(_score);
		Director::sharedDirector()->replaceScene(TransitionFade::create(0.7f, over));
    }
    _score += dt * (100 + _coffee);
    
    this->executeWalkAnimation();
    
}

float Player::getSpeed() {
    return _speedFactor + _coffee * kCoffeePower;
}

void Player::handleCollision(GameObject *gameObject) {
    
    switch(gameObject->getType()) {
            
        case GameObjectTypeMan:
        case GameObjectTypeWoman:
        case GameObjectTypeManager:
        {
            if (_damageTime > 0)
                return;
            
            _damageTime = 0.3f;
            
            Enemy *enemy = (Enemy *)gameObject;
            _life -= kDamageBaseAmount * enemy->getDamageFactor();
            
            b2Vec2 vel = _body->GetLinearVelocity();
            b2Vec2 enemyVel = enemy->getBody()->GetLinearVelocity();
            
            b2Vec2 targetVel;
            
            float maxForce = 0;
            
            if (this->getMovingHorizontalState() == MovingStateHorizontalStopped && this->getMovingVerticalState() == MovingStateVerticalStopped) {
                
                targetVel.x = enemyVel.x * 40;
                targetVel.y = enemyVel.y * 40;
                
                maxForce = kDamageMaxForceStopped;
                
            } else {
                
                targetVel.x = vel.x * -12;
                targetVel.y = vel.y * -12;
                
                maxForce = kDamageMaxForce;
                
            }
            
            if (targetVel.x >  maxForce) { targetVel.y *=  maxForce / targetVel.x; targetVel.x =  maxForce; }
            if (targetVel.x < -maxForce) { targetVel.y *= -maxForce / targetVel.x; targetVel.x = -maxForce; }
            if (targetVel.y >  maxForce) { targetVel.x *=  maxForce / targetVel.y; targetVel.y =  maxForce; }
            if (targetVel.y < -maxForce) { targetVel.x *= -maxForce / targetVel.y; targetVel.y = -maxForce; }
            
            _body->ApplyLinearImpulse(targetVel, _body->GetWorldCenter());
            
        }
            break;
            
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
            _coffee -= kDonutEffectAmount;
            if (_coffee < 0.0f)
                _coffee = 0.0f;
            gameObject->setState(GameObjectStateDead);
            
            break;
            
        case GameObjectTypeDonut:
            _life += kDonutEffectAmount;
            if (_life > 100.0f)
                _life = 100.0f;
            gameObject->setState(GameObjectStateDead);
            
            break;
            
        default:
            break;
    }
    

}

void Player::handleMovement(float angle) {
    
    if (_damageTime > 0)
        return;
    
    GameObject::handleMovement(angle);
}
