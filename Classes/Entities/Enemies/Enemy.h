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
#include "../Player.h"

class Enemy : public GameObject {
    
protected:
	
	virtual void handleCollision(GameObject *gameObject);

	Player* _playerReference;
    
	int _drinkedCoffee;
    float _randomMovingTime;
    bool _isRandomMoving;
    Point _walkingPoint;

public:
    
    virtual bool init(b2World *world, Dictionary *properties, Player* ref);
    virtual void update(float dt);
    virtual void updatePosition(Point position);

	virtual void handleMovement();
    virtual void die();
	virtual void finishedDyingAction();
    virtual bool isNearPlayer();
    
    CC_SYNTHESIZE(float, _damageFactor, DamageFactor);
    CC_SYNTHESIZE(float, _sightRange, SightRange);
    CC_SYNTHESIZE(bool, _randomMoveOnly, RandomMoveOnly);


};

#endif /* defined(__CampJam__Player__) */
