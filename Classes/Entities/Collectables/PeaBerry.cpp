#include "PeaBerry.h"

bool PeaBerry::init(b2World *world, Dictionary *properties) {
    
	_node = Sprite::createWithSpriteFrameName("special_coffee.png");
    
	this->setType(GameObjectTypePeaBerry);

    if (!GameObject::init(world, properties, true))
        return false;
    
    return true;
}