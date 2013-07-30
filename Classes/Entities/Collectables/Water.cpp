#include "Water.h"

bool Water::init(b2World *world, Dictionary *properties) {
    
    _node = Sprite::createWithSpriteFrameName("water.png");
	
	this->setType(GameObjectTypeWater);
    
    if (!GameObject::init(world, properties, true))
        return false;
    
    return true;
}