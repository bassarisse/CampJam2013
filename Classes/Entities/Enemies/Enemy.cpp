
#include "Enemy.h"

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
    if(_state == GameObjectStateDying || _state == GameObjectStateDead)
		return;

    GameObject::update(dt);
    
    Sprite *sprite = (Sprite *)_node;
    if (sprite->getOpacity() < 255) {
        int newOpacity = sprite->getOpacity() + dt * 500;
        if (newOpacity > 255) newOpacity = 255;
        sprite->setOpacity(newOpacity);
    }
    
    _randomMovingTime -= dt;
    
    this->executeWalkAnimation();
    
    int colorAdd = 255 - 60 * _drinkedCoffee;
    Sprite *thisSprite = (Sprite *)this->getNode();
    thisSprite->setColor(ccc3(255, colorAdd, colorAdd));
    
	if(_drinkedCoffee >= kEnemyDeathCoffeeNumber) {
        this->die();
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

void Enemy::die() {
    
    this->setState(GameObjectStateDying);
    _playerReference->setScore(_playerReference->getScore() + kEnemyScore);
    
    FadeOut* dying = FadeOut::create(1.5f);
    JumpTo* deathLeap = JumpTo::create(0.75f, ccp(_node->getPosition().x, _node->getPosition().y), 40, 1);
    Sequence* deathSequence = Sequence::create(dying,
                                               CallFunc::create(this, callfunc_selector(Enemy::finishedDyingAction)),
                                               NULL);
    Spawn* deathRitual = Spawn::create(deathLeap, deathSequence, NULL);
	
    _playerReference->getGameScreen()->showScore(ccp(
                                                     _node->getPosition().x + (_node->getContentSize().width * 0.25f),
                                                     _node->getPosition().y + (_node->getContentSize().height * 0.25f)
                                                     ), kEnemyScore);
    _node->runAction(deathRitual);
    
}

void Enemy::finishedDyingAction() {
	this->setState(GameObjectStateDead);
}

bool Enemy::isNearPlayer() {
    
    Point playerPosition = _playerReference->getNode()->getPosition();
    Point thisPosition = this->getNode()->getPosition();
    
    float xDifference = abs(playerPosition.x - thisPosition.x);
    float yDifference = abs(playerPosition.y - thisPosition.y);
    
    return (_sightRange == 0 || xDifference <= _sightRange || yDifference <= _sightRange);

}