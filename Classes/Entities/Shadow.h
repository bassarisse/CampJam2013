#ifndef __CAMPJAM_SHADOW_H
#define __CAMPJAM_SHADOW_H

#include "cocos2d.h"

class GameObject;

using namespace cocos2d;

class Shadow : public Node {
    
public:
	CC_SYNTHESIZE(GameObject*, _baseEntity, BaseEntity);

    static Shadow *create(GameObject* baseEntity);
    virtual void draw();

    
};
#endif // __CAMPJAM_SHADOW_H__