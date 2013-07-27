//
//  GameObject.h
//  PlatformerTest
//
//  Created by Bruno Assarisse on 23/07/13.
//
//

#ifndef __PlatformerTest__GameObject__
#define __PlatformerTest__GameObject__

#include "cocos2d.h"
#include "Box2D.h"
#include "Common.h"

using namespace cocos2d;

class BAContactListener;

class SensorTypeContainer {
public:
    SensorType sensorType;
};

class GameObject : public Object {
    
protected:
    
    b2Body *_body;
    Node *_node;
    
    virtual void setProperties(Dictionary *properties);
    virtual void addCircularFixture(float radius);
    virtual void addRectangularFixture(float width, float height);
    virtual void createFixture(b2Shape *shape);
    virtual void addFixtures();
    
    
public:
    
    GameObject();
    virtual ~GameObject();
    
    BAContactListener *contactListener;
    
    Node* getNode();
    
    virtual void addBodyToWorld(b2World *world);
    virtual bool init(b2World *world, Dictionary *properties);
    virtual void update(float dt);
    
    CC_SYNTHESIZE(MovingHorizontalState, _movingHorizontalState, MovingHorizontalState);
    CC_SYNTHESIZE(MovingVerticalState, _movingVerticalState, MovingVerticalState);
    CC_SYNTHESIZE(GameObjectState, _state, State);
    
};

#endif /* defined(__PlatformerTest__GameObject__) */