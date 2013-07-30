#include "Coffee.h"

bool Coffee::init(b2World *world, Dictionary *properties) {
    
    _node = Sprite::createWithSpriteFrameName("coffee.png");
	
	this->setType(GameObjectTypeCoffee);

    if (!GameObject::init(world, properties, true))
        return false;
    
    return true;
}