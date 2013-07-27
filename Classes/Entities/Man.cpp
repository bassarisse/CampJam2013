#include "Man.h"

Man::~Man() {
	
}


void Man::addFixtures() {
	
	float width = _node->getContentSize().width;// * 0.75f;
    float height = _node->getContentSize().height;// * 0.8f;
    //this->addCircularFixture(width / 2);
    this->addRectangularFixture(width, height);

}

bool Man::init(b2World *world, Dictionary *properties, Player *ref) {
	
	//FIXME
	_node = Sprite::createWithSpriteFrameName("enemydown1.png");

	_damageFactor = 0.3f;
	_speedFactor = 1.0f;
	
	_type = GameObjectTypeMan;

	if (!Enemy::init(world, properties, ref))
        return false;
    
    return true;
}

void Man::update(float dt) {
	Enemy::update(dt);
	
	b2Vec2 playerPosition = _playerReference->getPosition();
	b2Vec2 manPosition = _body->GetPosition();
	
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
	}



}

void Man::handleCollisions() {
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