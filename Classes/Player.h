//
//  Player.h
//  PlatformerTest
//
//  Created by Bruno Assarisse on 23/07/13.
//
//

#ifndef __PlatformerTest__Player__
#define __PlatformerTest__Player__

#include "GameObject.h"

class Player : public GameObject {
    
private:
    
protected:
    
    virtual void addFixtures();
    virtual void createSensorFixture(b2Shape *shape, SensorTypeContainer *sensorTypeContainer);
    
public:
    
    virtual ~Player();
    
    virtual bool init(b2World *world, Dictionary *properties);
    virtual void update(float dt);
    
};

#endif /* defined(__PlatformerTest__Player__) */
