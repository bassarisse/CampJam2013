//
//  Enemy.h
//  CampJam13
//
//  Created by Murilo Clemente - 27/07/13
//
//

#ifndef __CampJam__Enemy__
#define __CampJam__Enemy__

#include "GameObject.h"

class Enemy : public GameObject {
    
private:
    
protected:
    
    virtual void addFixtures();
    virtual void createSensorFixture(b2Shape *shape, SensorTypeContainer *sensorTypeContainer);
    
public:
    
    virtual ~Enemy();
    
    virtual bool init(b2World *world, Dictionary *properties);
    virtual void update(float dt);
    
	float damageFactor;
	float speedFactor;

};

#endif /* defined(__PlatformerTest__Player__) */
