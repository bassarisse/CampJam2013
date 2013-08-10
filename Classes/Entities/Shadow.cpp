#include "Shadow.h"

#include "Common.h"
#include "../GameObject.h"

void Shadow::draw() {
    
	if(!_baseEntity) {
		this->stopAllActions();
		this->removeFromParentAndCleanup(true);
	}
	 
    Node::draw();
	
	glEnable(GL_LINE_SMOOTH);
	//glColor4ub(0, 255, 0, 255);
	glLineWidth(1);
    
	Size entitySize = _baseEntity->getNode()->getContentSize();
	b2Vec2 bodyPosition = _baseEntity->getBody()->GetPosition();
	Point entityPosition = ccp(bodyPosition.x * PTM_RATIO, bodyPosition.y * PTM_RATIO);
    
	ccDrawColor4B(0, 0, 0, 20);
	ccDrawCircle(
                 ccp(entityPosition.x, entityPosition.y - (entitySize.height / 2.4f)),
                 entitySize.width / 4.4f,
                 0, 200, false, 1.0f, 0.15f);

	//ccDrawColor4B(0, 0, 0, 100);
    // https://github.com/cocos2d/cocos2d-x/issues/2287
	ccDrawFilledCircle(
                       ccp(entityPosition.x, entityPosition.y - (entitySize.height / 2.4f)),
                       entitySize.width / 4.5f,
                       0, 200, false, 1.0f, 0.15f);

	// restore original values
	glColor4ub(255, 255, 255, 255);
	glLineWidth(1);
	glPointSize(1);
}

Shadow* Shadow::create(GameObject* baseEntity) {
    Shadow *pRet = new Shadow();
    if (pRet && pRet->init())
    {
		pRet->setBaseEntity(baseEntity);
        pRet->autorelease();
        return pRet;
    }
    else
    {
        CC_SAFE_DELETE(pRet);
        return NULL;
    }
}