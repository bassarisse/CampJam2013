//
//  Player.h
//  CampJam
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
    
    bool _isFollowingPoint;
    bool _isUnderPeaBerryEffect;
    float _peaBerryTime;
    float _damageTime;
    Point _pointToFollow;
    
    virtual void addFixtures();
    virtual float getSpeed();
	virtual void handleCollision(GameObject *gameObject);
	virtual void handleMovement();
	virtual void handleMovement(float angle);
    
public:
    
    virtual ~Player();
    
    virtual bool init(b2World *world, Dictionary *properties);
    virtual void update(float dt);
    virtual void followPoint(Point point);
    virtual void stopFollowingPoint();
    
	CC_SYNTHESIZE(float, _score, Score);
	CC_SYNTHESIZE(float, _coffee, Coffee);
	CC_SYNTHESIZE(float, _life, Life);

};

#endif /* defined(__CampJam__Player__) */
