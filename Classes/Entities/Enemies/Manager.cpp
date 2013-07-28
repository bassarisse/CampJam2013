#include "Manager.h"

Manager::~Manager() {
	
}


void Manager::addFixtures() {
    
    float width = _node->getContentSize().width * 0.32f;
    float height = _node->getContentSize().height * 0.2f;
    //this->addCircularFixture(width / 2);
    this->addRectangularFixture(0, -height * 2, width, height);

}

bool Manager::init(b2World *world, Dictionary *properties, Player *ref) {
	
	//FIXME
	_node = Sprite::createWithSpriteFrameName("manager_down.png");
    _spriteFrameName = "manager";
    
	_damageFactor = 1.5f;
    
	this->setType(GameObjectTypeManager);
	
	if (!Enemy::init(world, properties, ref))
        return false;
    
	_speedFactor = -4.5f;
    _shouldFlipSprite = false;
    
    return true;
}

void Manager::executeWalkAnimation() {
    
    if (this->getState() == GameObjectStateWalking) {
        
        float speed = (abs(kWalkForce + this->getSpeed())) / 1.9f;
        
        Speed *walkAction = dynamic_cast<Speed*>(_node->getActionByTag(kWalkActionTag));
        
        if (!walkAction) {
            
            SpriteFrameCache *spriteCache = SpriteFrameCache::sharedSpriteFrameCache();
            
            const char *frameNameVertical = getDirectionName(_lastVerticalDirection);
            
            Animation *anim = Animation::create();
            anim->setDelayPerUnit(0.15f);
            anim->setRestoreOriginalFrame(true);
            
            anim->addSpriteFrame(spriteCache->spriteFrameByName(String::createWithFormat("%s_%s1.png", _spriteFrameName, frameNameVertical)->getCString()));
            anim->addSpriteFrame(spriteCache->spriteFrameByName(String::createWithFormat("%s_%s.png", _spriteFrameName, frameNameVertical)->getCString()));
            anim->addSpriteFrame(spriteCache->spriteFrameByName(String::createWithFormat("%s_%s2.png", _spriteFrameName, frameNameVertical)->getCString()));
            anim->addSpriteFrame(spriteCache->spriteFrameByName(String::createWithFormat("%s_%s.png", _spriteFrameName, frameNameVertical)->getCString()));
            
            walkAction = Speed::create(RepeatForever::create(Animate::create(anim)), speed);
            walkAction->setTag(kWalkActionTag);
            
            _node->stopAllActions();
            _node->runAction(walkAction);
        }
        
        walkAction->setSpeed(speed);
        
    } else if (this->getState() == GameObjectStateStanding) {
        
        _node->stopAllActions();
        this->setIdleFrame();
        
    }
}