
#include "Enemy.h"

Enemy::~Enemy() {
    
}

void Enemy::addFixtures() {
	
}

bool Enemy::init(b2World *world, Dictionary *properties, Player *ref) {
    
    //_node = Sprite::createWithSpriteFrameName("right1.png");
	_playerReference = ref;
    _drinkedCoffee = 0;
    
    _sightRange = 0.0f;
    _randomMoveOnly = false;
    _randomMovingTime = 0.0f;
    _isRandomMoving = false;
    _walkingPoint = ccp(0, 0);
    
    String *randomOnly = (String *)properties->objectForKey("Random");
    if (randomOnly)
        _randomMoveOnly = true;
    
    String *sight = (String *)properties->objectForKey("Sight");
    if (sight)
        _sightRange = sight->intValue();

    if (!GameObject::init(world, properties))
        return false;
    
    return true;
}

void Enemy::handleMovement() {
    
    _randomMoveOnly = true;
    
    if (!_randomMoveOnly && this->isNearPlayer()) {
        _isRandomMoving = false;
        GameObject::handleMovement(this->getAngleForPoint(_playerReference->getNode()->getPosition()));
    } else {
        
        Point thisPosition = this->getNode()->getPosition();
        
        if (!_isRandomMoving || _randomMovingTime <= 0) {
            _walkingPoint = ccp(thisPosition.x, thisPosition.y);
            _randomMovingTime = kEnemyRandomTime;
        }
        
        while (abs(_walkingPoint.x - thisPosition.x) <= 5 && abs(_walkingPoint.y - thisPosition.y) <= 5) {
            int x = (thisPosition.x + rand() % (kEnemyRandomRange + 1)) - kEnemyRandomRange / 2;
            int y = (thisPosition.y + rand() % (kEnemyRandomRange + 1)) - kEnemyRandomRange / 2;
            _walkingPoint = ccp(x, y);
        }
        
        _isRandomMoving = true;
        GameObject::handleMovement(this->getAngleForPoint(_walkingPoint));
    }
}

void Enemy::update(float dt) {
    
    GameObject::update(dt);
    
    _randomMovingTime -= dt;
    
    this->executeWalkAnimation();
    
    int colorAdd = 255 - 60 * _drinkedCoffee;
    Sprite *thisSprite = (Sprite *)this->getNode();
    thisSprite->setColor(ccc3(255, colorAdd, colorAdd));
    
	if(_drinkedCoffee >= kEnemyDeathCoffeeNumber && _state != GameObjectStateDead) {
        this->setState(GameObjectStateDead);
        _playerReference->setScore(_playerReference->getScore() + kEnemyScore);
    }
    
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

bool Enemy::isNearPlayer() {
    
    Point playerPosition = _playerReference->getNode()->getPosition();
    Point thisPosition = this->getNode()->getPosition();
    
    float xDifference = abs(playerPosition.x - thisPosition.x);
    float yDifference = abs(playerPosition.y - thisPosition.y);
    
    return (_sightRange == 0 || xDifference <= _sightRange || yDifference <= _sightRange);
}