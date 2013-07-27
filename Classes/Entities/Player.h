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
        
protected:
    
    virtual void addFixtures();
    virtual float getSpeed();
	virtual void handleCollision(GameObject *gameObject);
    
public:
    
    virtual ~Player();
    
    virtual bool init(b2World *world, Dictionary *properties);
    virtual void update(float dt);


	CC_SYNTHESIZE(float, _coffee, Coffee);
	CC_SYNTHESIZE(float, _life, Life);

};

#endif /* defined(__PlatformerTest__Player__) */
