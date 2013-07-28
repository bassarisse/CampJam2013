
#include "Enemy.h"

Enemy::~Enemy() {
    
}

void Enemy::addFixtures() {
	
}

bool Enemy::init(b2World *world, Dictionary *properties, Player *ref) {
    
    //_node = Sprite::createWithSpriteFrameName("right1.png");
	_playerReference = ref;
    _drinkedCoffee = 0;

    if (!GameObject::init(world, properties))
        return false;
    
    return true;
}

void Enemy::handleMovement() {
	GameObject::handleMovement(this->getAngleForPoint(_playerReference->getNode()->getPosition()));
}

void Enemy::update(float dt) {
    if(_state == GameObjectStateDying || _state == GameObjectStateDead)
		return;

    GameObject::update(dt);
    
    this->executeWalkAnimation();
    
    int colorAdd = 255 - 60 * _drinkedCoffee;
    Sprite *thisSprite = (Sprite *)this->getNode();
    thisSprite->setColor(ccc3(255, colorAdd, colorAdd));
    
	if(_drinkedCoffee >= kEnemyDeathCoffeeNumber && _state != GameObjectStateDead) {
		FadeOut* dying = FadeOut::create(1.5f);
		JumpTo* deathLeap = JumpTo::create(0.75f, ccp(_node->getPosition().x,_node->getPosition().y), 15, 1);
		Sequence* deathSequence = Sequence::create(dying, CallFunc::create(this, callfunc_selector(Enemy::finishedDyingAction)), NULL);
		Spawn* deathRitual = Spawn::create(deathLeap, deathSequence, NULL);
	
		_playerReference->getGameScreen()->showScore(ccp(
													_node->getPosition().x + (_node->getContentSize().width / 2),
													_node->getPosition().y + (_node->getContentSize().height / 2 ),
													), kEnemyScore);
		this->setState(GameObjectStateDying);
		_node->runAction(deathRitual);
        
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

void Enemy::finishedDyingAction() {
	this->setState(GameObjectStateDead);
}