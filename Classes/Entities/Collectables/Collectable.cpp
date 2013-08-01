
#include "Collectable.h"

void Collectable::addFixtures() {
	float width = _node->getContentSize().width * 0.6f;
    //float height = _node->getContentSize().height * 0.6f;
    
    //this->addRectangularFixture(width, height);
    this->addCircularFixture(width / 2);
}

void Collectable::update(float dt) {
    if(_state == GameObjectStateDying || _state == GameObjectStateDead)
		return;
    
    GameObject::update(dt);
    
    Sprite *sprite = (Sprite *)_node;
    if (sprite->getOpacity() < 255) {
        int newOpacity = sprite->getOpacity() + dt * 600;
        if (newOpacity > 255) newOpacity = 255;
        sprite->setOpacity(newOpacity);
    }
    
}