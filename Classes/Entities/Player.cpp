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

bool Player::init(b2World *world, Dictionary *properties, GamePlay* gameScreen) {
    
    _isFollowingPoint = false;
    _isUnderPeaBerryEffect = false;
	_score = 0;
    _node = Sprite::createWithSpriteFrameName("stag_down.png");
    _life = 100.0f;
    _coffee = 0.0f;
    _hasEmptyPaper = false;
    _hasDocument = false;
    _copiesQty = 0;
    
    _spriteFrameName = "stag";
    
    this->setType(GameObjectTypePlayer);
    
	_gameScreen = gameScreen;

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
        _life -= (dt * kCoffeeLifeDamage) * (0.8f + _coffee / 100.0f);
    }
    
    if (_life < 0) {
		SimpleAudioEngine::sharedEngine()->playEffect("wilhem.wav");
		Scene* over = GameoverScene::scene(_score);
		Director::sharedDirector()->replaceScene(over);
		return;
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
            
			SimpleAudioEngine::sharedEngine()->playEffect("player_hit.wav");
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
            
            /*
             * Collectables
             */
            
        case GameObjectTypeCoffee:
            _coffee += kCoffeeLevelAdd;
            if (_coffee > 100.0f)
                _coffee = 100.0f;
            gameObject->setState(GameObjectStateDead);
			_gameScreen->getCoffeeBar()->blinkBar();
			
            break;
            
        case GameObjectTypePeaBerry:
            if (!_isUnderPeaBerryEffect)
                _speedFactor += kPeaBerrySpeedFactor;
            _isUnderPeaBerryEffect = true;
            _peaBerryTime = kPeaBerryTime;
            gameObject->setState(GameObjectStateDead);
			_gameScreen->getCoffeeBar()->blinkBar();
            break;
            
        case GameObjectTypeWater:
            _coffee -= kWaterEffectAmount;
            if (_coffee < 0.0f)
                _coffee = 0.0f;
            gameObject->setState(GameObjectStateDead);
            _gameScreen->getCoffeeBar()->blinkBar();
            break;
            
        case GameObjectTypeDonut:
            _life += kDonutEffectAmount;
            if (_life > 100.0f)
                _life = 100.0f;
            gameObject->setState(GameObjectStateDead);
			_gameScreen->getHealthBar()->blinkBar();
            break;
            
            /*
             * Static
             */
            
        case GameObjectTypeEmptyPaper:
            _hasEmptyPaper = true;
            break;
            
        case GameObjectTypeDocument:
            _hasDocument = true;
            break;
            
        case GameObjectTypePrinter:
            if (_hasEmptyPaper && _hasDocument) {
                _copiesQty++;
                _hasEmptyPaper = false;
                _hasDocument = false;
            }
            break;
            
        case GameObjectTypeBossDesk:
            if (_copiesQty > 0) {
                int addedScore = 4000 * _copiesQty;
                
                _score += addedScore;

				if(_copiesQty > 1) {
					addedScore = addedScore * (1 + (_copiesQty / 50));  
				}
				_copiesQty = 0;
				
                _gameScreen->showScore(_node->getPosition(), addedScore);
            }
            break;
            
        default:
            break;
    }
    
}

void Player::followPoint(Point point) {
    _isFollowingPoint = true;
    _pointToFollow = point;
}

void Player::stopFollowingPoint() {
    _isFollowingPoint = false;
}

void Player::handleMovement() {
    
    if (!_isFollowingPoint) {
        GameObject::handleMovement();
        return;
    }
    
    this->handleMovement(this->getAngleForPoint(_pointToFollow));
    
}

void Player::handleMovement(float angle) {
    
    if (_damageTime > 0)
        return;
    
    GameObject::handleMovement(angle);
}
