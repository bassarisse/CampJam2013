//
//  GameObject.h
//  CampJam
//
//  Created by Bruno Assarisse on 23/07/13.
//
//

#ifndef __CampJam__GameObject__
#define __CampJam__GameObject__

#include "cocos2d.h"
#include <Box2D/Box2D.h>
#include "Common.h"
#include "BAContactListener.h"

using namespace cocos2d;

class SensorTypeContainer {
public:
    SensorType sensorType;
};

class GameObject : public Object {
    
protected:
    
    b2Body *_body;
    Node *_node;
    bool _isSensor;
    bool _shouldFlipSprite;
    std::vector<GameObject *> _contacts;
    kDirection _lastDirection;
    kDirection _lastVerticalDirection;
    kDirection _lastHorizontalDirection;
    float _speedFactor;
    const char* _spriteFrameName;
    
    virtual void setProperties(Dictionary *properties);
    virtual void addCircularFixture(float radius);
    virtual void addRectangularFixture(float width, float height);
    virtual void addRectangularFixture(float x, float y, float width, float height);
    virtual void createFixture(b2Shape *shape);
    virtual void addFixtures();
    virtual void createSensorFixture(b2Shape *shape, SensorTypeContainer *sensorTypeContainer);
    virtual float getSpeed();
    virtual void executeWalkAnimation();
    virtual void setIdleFrame();
	virtual void handleCollisions();
	virtual void handleCollision(GameObject *gameObject);
    
public:
    
    GameObject();
    virtual ~GameObject();
    
    Node* getNode();
	b2Body* getBody();

    virtual void addContact(GameObject *contact);
    virtual void removeContact(GameObject *contact);
    
    virtual void addBodyToWorld(b2World *world);
    virtual bool init(b2World *world, Dictionary *properties);
    virtual bool init(b2World *world, Dictionary *properties, bool isSensor);
    virtual void update(float dt);
    virtual void handleMovement();
    virtual void handleMovement(float angle);
    virtual bool changeDirection(kDirection direction);
    
	

    CC_SYNTHESIZE(MovingHorizontalState, _movingHorizontalState, MovingHorizontalState);
    CC_SYNTHESIZE(MovingVerticalState, _movingVerticalState, MovingVerticalState);
    CC_SYNTHESIZE(GameObjectState, _state, State);
    CC_SYNTHESIZE(GameObjectType, _type, Type);
    
};

#endif /* defined(__CampJam__GameObject__) */