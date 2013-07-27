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
    
    float _jumpTime;
    
    b2Body *_body;
    Node *_node;
    
    virtual void setProperties(Dictionary *properties);
    virtual void addCircularFixture(float radius);
    virtual void addRectangularFixture(float width, float height);
    virtual void createFixture(b2Shape *shape);
    virtual void addFixtures();
    
    virtual bool canJump();
    virtual bool isHittingHead();
    
public:
    
    GameObject();
    virtual ~GameObject();
    
    BAContactListener *contactListener;
    
    Node* getNode();
    
    virtual void addBodyToWorld(b2World *world);
    virtual bool init(b2World *world, Dictionary *properties);
    virtual void update(float dt);
    virtual void jump();
    virtual void finishJump();
    
    CC_SYNTHESIZE(MovingState, _movingState, MovingState);
    CC_SYNTHESIZE(GameObjectState, _state, State);
    
};

inline float floatValue(Object* o)
{
    String* string = dynamic_cast<String*>(o);
    if (string)
        return string->floatValue();
    return 0.0f;
}

#endif /* defined(__PlatformerTest__GameObject__) */