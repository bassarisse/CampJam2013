#include "Shadow.h"


void Shadow::draw() {
	if(!_baseEntity) {
		this->stopAllActions();
		this->removeFromParentAndCleanup(true);
	}
	 
    Node::draw();
	

	glEnable(GL_LINE_SMOOTH);
	glLineWidth(1);
	//glColor4ub(0, 255, 0, 255);
	ccDrawColor4B(0,0,0,50);
	Size entitySize = _baseEntity->getNode()->getContentSize();
	Point entityPosition = _baseEntity->getNode()->getPosition();
	ccDrawCircle(
		ccp(entityPosition.x, entityPosition.y - (entitySize.height / 2.3)), 
		entitySize.width / 2.8,
		0, 200, false, 1, 0.15);

	// restore original values
	glLineWidth(1);
	glColor4ub(255,255,255,255);
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