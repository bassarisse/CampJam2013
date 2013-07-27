
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
	b2Vec2 playerPosition = _playerReference->getPosition();
	b2Vec2 manPosition = _body->GetPosition();
	
	float angle = atan2(manPosition.y - playerPosition.y, 
						manPosition.x - playerPosition.x) + 180;

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
	
	GameObject::handleMovement(angle * 180 / M_PI); //degree conversion
}


void Enemy::update(float dt) {
    
    GameObject::update(dt);
    
	
	/*
	if(playerPosition.x > manPosition.x) {
		this->setMovingHorizontalState(MovingStateRight);
	} else //if(playerPosition.x < manPosition.x) 
	{
		this->setMovingHorizontalState(MovingStateLeft);
	}

	if(playerPosition.y > manPosition.y) {
		this->setMovingVerticalState(MovingStateUp);
	} else 
	{
		this->setMovingVerticalState(MovingStateDown);
	}*/
}

void Enemy::handleCollisions()  {
	//Override this shit!
}