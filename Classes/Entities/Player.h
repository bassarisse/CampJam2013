//
//  Player.h
//  PlatformerTest
//
//  Created by Bruno Assarisse on 23/07/13.
//
//

#ifndef __CampJam__Player__
#define __CampJam__Player__

#include "GameObject.h"

class Player : public GameObject {
    
private:
    
    float _life;
    float _coffee;
    float _speedFactor;
    
protected:
    
    virtual void addFixtures();
	virtual void handleCollisions();
    
public:
    
    virtual ~Player();
    
    virtual bool init(b2World *world, Dictionary *properties);
    virtual void update(float dt);
    
};

#endif /* defined(__PlatformerTest__Player__) */
