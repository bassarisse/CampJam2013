#include "Man.h"

Man::~Man() {
	
}


void Man::addFixtures() {
    
    float width = _node->getContentSize().width * 0.32f;
    float height = _node->getContentSize().height * 0.2f;
    //this->addCircularFixture(width / 2);
    this->addRectangularFixture(0, -height * 2, width, height);

} 

bool Man::init(b2World *world, Dictionary *properties, Player *ref) {
	
	//FIXME
	_node = Sprite::createWithSpriteFrameName("man_down.png");
    _spriteFrameName = "man";
    
    _damageFactor = 0.3f;
	_speedFactor = 1.0f;
	_drinkedCoffee = 0;

	this->setType(GameObjectTypeMan);
	
	if (!Enemy::init(world, properties, ref))
        return false;
    
    return true;
}

void Man::update(float dt) {
	Enemy::update(dt);

	if(_drinkedCoffee >= kEnemyDeathCoffeeNumber) {

		if(_state != GameObjectStateDead)
			this->setState(GameObjectStateDead);
	
	}

}

void Man::handleCollisions() {
	for(std::vector<GameObject*>::size_type i = 0; i < _contacts.size(); i++)
	{
		GameObject* collisionObject = _contacts[i];
		if(!collisionObject)
			continue;
		
		switch(collisionObject->getType()) {
            case GameObjectTypeCoffee:
                _speedFactor += 0.15f;
                _drinkedCoffee++;
                collisionObject->setState(GameObjectStateDead);
                
                break;
            default:
                break;
		}
		
        
		
	}

}