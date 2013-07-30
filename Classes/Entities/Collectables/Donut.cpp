#include "Donut.h"

bool Donut::init(b2World *world, Dictionary *properties) {
    
    _node = Sprite::createWithSpriteFrameName("donut.png");
	
	this->setType(GameObjectTypeDonut);

    if (!GameObject::init(world, properties, true))
        return false;
    
    return true;
}