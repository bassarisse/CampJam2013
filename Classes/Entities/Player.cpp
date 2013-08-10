//
//  Player.cpp
//  CampJam
//
//  Created by Bruno Assarisse on 23/07/13.
//
//

#include "Player.h"
#include "../GamePlay.h"
#include "Enemies/Enemy.h"
#include "SimpleAudioEngine.h"
#include "../Scenes/GameoverScene.h"

using namespace CocosDenshion;

Player::~Player() {
    
}

void Player::addFixtures() {
    
    float width = _node->getContentSize().width * 0.32f;
    float height = _node->getContentSize().height * 0.2f;
    
    this->addCircularFixture(0, -height * 2, width / 2);
    //this->addRectangularFixture(0, -height * 2, width, height);
    
}

bool Player::init(b2World *world, Dictionary *properties, GamePlay* gameScreen) {
    
    _isFollowingPoint = false;
	_pointToFollow = ccp(0, 0);
    _isUnderPeaBerryEffect = false;
	_peaBerryTime = 0.0f;
	_damageTime = 0.0f;
	_score = 0.0f;
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
			_gameScreen->getCoffeeBar()->setPeaBerry(false);
        }
    }
    
    float affectValue = dt * kCoffeeDamage;
    
    _coffee -= affectValue;
    if (_coffee < 0) _coffee = 0;
    
    if (_coffee > kCoffeeThreshold) {
        _life -= (dt * kCoffeeLifeDamage) * (0.8f + _coffee / 100.0f);
    }
    
    if (_life < 0) {
        
        int bestScore = UserDefault::sharedUserDefault()->getIntegerForKey("Record", 0);
        
        bool isRecord = _score > bestScore;
        
        if (isRecord) {
            UserDefault::sharedUserDefault()->setIntegerForKey("Record", _score);
            UserDefault::sharedUserDefault()->flush();
        }
        
		SimpleAudioEngine::sharedEngine()->playEffect("wilhem.wav");
		Scene* over = GameoverScene::scene(_score, isRecord);
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
            
            Point thisPosition = _node->getPosition();
            Point enemyPosition = enemy->getNode()->getPosition();
            
            float angleFromEnemy = 180 + atan2(enemyPosition.y - thisPosition.y,
                                               enemyPosition.x - thisPosition.x) * 180 / M_PI;
            
            float angleFromPlayer = 180 + atan2(thisPosition.y - enemyPosition.y,
                                                thisPosition.x - enemyPosition.x) * 180 / M_PI;
            
            float playerImpulseX = kDamageImpulse * cos(angleFromEnemy * M_PI / 180.0f);
            float playerImpulseY = kDamageImpulse * sin(angleFromEnemy * M_PI / 180.0f);
            
            float enemyImpulseX = kDamageImpulse * 0.96f * cos(angleFromPlayer * M_PI / 180.0f);
            float enemyImpulseY = kDamageImpulse * 0.96f * sin(angleFromPlayer * M_PI / 180.0f);
            
            b2Vec2 playerImpulse = b2Vec2(playerImpulseX, playerImpulseY);
            b2Vec2 enemyImpulse = b2Vec2(enemyImpulseX, enemyImpulseY);
            
            enemy->getBody()->ApplyLinearImpulse(enemyImpulse, _body->GetWorldCenter());
            _body->ApplyLinearImpulse(playerImpulse, _body->GetWorldCenter());
            _gameScreen->shakeScreen();
            
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
			_gameScreen->getCoffeeBar()->setPeaBerry(true);
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
            if (!_hasEmptyPaper)
                SimpleAudioEngine::sharedEngine()->playEffect("paper.wav");
            _hasEmptyPaper = true;
            break;
            
        case GameObjectTypeDocument:
            if (!_hasDocument)
                SimpleAudioEngine::sharedEngine()->playEffect("paper.wav");
            _hasDocument = true;
            break;
            
        case GameObjectTypePrinter:
            if (_hasEmptyPaper && _hasDocument) {
                SimpleAudioEngine::sharedEngine()->playEffect("printer.wav");
                _copiesQty++;
                _hasEmptyPaper = false;
                _hasDocument = false;
            }
            break;
            
        case GameObjectTypeBossDesk:
            if (_copiesQty > 0) {
                SimpleAudioEngine::sharedEngine()->playEffect("paper.wav");
                int addedScore = kCopyScore * _copiesQty;
                
                _score += addedScore;

				if(_copiesQty > 1) {
					//float factor = (float)((float)_copiesQty / 50.0f);
					addedScore = addedScore * (1 + (_copiesQty / 50.0f));  
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
