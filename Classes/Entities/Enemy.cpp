
#include "Enemy.h"

Enemy::~Enemy() {
    
}

void Enemy::addFixtures() {
	
}

bool Enemy::init(b2World *world, Dictionary *properties, Player *ref) {
    
    //_node = Sprite::createWithSpriteFrameName("right1.png");
	_playerReference = ref;

    if (!GameObject::init(world, properties))
        return false;
    
    return true;
}

void Enemy::handleMovement() {
	Point playerPosition = _playerReference->getNode()->getPosition();
	Point manPosition = _node->getPosition();
	
	float angle = 180 + atan2(manPosition.y - playerPosition.y,
						manPosition.x - playerPosition.x) * 180 / M_PI; //degree conversion

	//float angle = atan2(playerPosition.y - manPosition.y, 
	//					playerPosition.x - manPosition.x);
    
	if(angle == 0 || angle == 360)
	{
		this->setMovingHorizontalState(MovingStateRight);
		this->setMovingVerticalState(MovingStateVerticalStopped);
	} else if(angle > 0 && angle < 90)
	{
		this->setMovingHorizontalState(MovingStateRight);
		this->setMovingVerticalState(MovingStateUp);
	} else if(angle == 90)
	{
		this->setMovingHorizontalState(MovingStateHorizontalStopped);
		this->setMovingVerticalState(MovingStateUp);
	} else if(angle > 90 && angle < 180)
	{
		this->setMovingHorizontalState(MovingStateLeft);
		this->setMovingVerticalState(MovingStateUp);
	} else if(angle == 180)
	{
		this->setMovingHorizontalState(MovingStateLeft);
		this->setMovingVerticalState(MovingStateVerticalStopped);
	} else if(angle > 180 && angle < 270)
	{
		this->setMovingHorizontalState(MovingStateLeft);
		this->setMovingVerticalState(MovingStateDown);
	} else if(angle == 270)
	{
		this->setMovingHorizontalState(MovingStateHorizontalStopped);
		this->setMovingVerticalState(MovingStateDown);
	} else if(angle > 270 && angle < 360)
	{
		this->setMovingHorizontalState(MovingStateRight);
		this->setMovingVerticalState(MovingStateDown);
	}
    
    if (this->getMovingHorizontalState() == MovingStateRight)
        _lastHorizontalDirection = kDirectionRight;
    else if (this->getMovingHorizontalState() == MovingStateLeft)
        _lastHorizontalDirection = kDirectionLeft;
    
    if (this->getMovingVerticalState() == MovingStateUp)
        _lastVerticalDirection = kDirectionUp;
    else if (this->getMovingVerticalState() == MovingStateDown)
        _lastVerticalDirection = kDirectionDown;
	
	GameObject::handleMovement(angle); 
}


void Enemy::update(float dt) {
    
    GameObject::update(dt);
    
    this->executeWalkAnimation();
    
}

void Enemy::handleCollisions()  {
    
	for(std::vector<GameObject*>::size_type i = 0; i < _contacts.size(); i++)
	{
		GameObject* collisionObject = _contacts[i];
		if(!collisionObject || collisionObject->getState() == GameObjectStateDead)
			continue;
		
		switch(collisionObject->getType()) {
            case GameObjectTypeCoffee:
                _speedFactor += 2.2f;
                _drinkedCoffee++;
                collisionObject->setState(GameObjectStateDead);
                
                break;
            default:
                break;
		}
		
	}
    
}