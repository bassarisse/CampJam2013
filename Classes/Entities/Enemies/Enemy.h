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
    
private:
    
protected:
    
    virtual void addFixtures();
	
	virtual void handleCollision(GameObject *gameObject);

	Player* _playerReference;

	int _drinkedCoffee;

public:
    
    virtual ~Enemy();
    
    virtual bool init(b2World *world, Dictionary *properties, Player* ref);
    virtual void update(float dt);

	virtual void handleMovement();

	void finishedDyingAction();
    
    CC_SYNTHESIZE(float, _damageFactor, DamageFactor);


};

#endif /* defined(__CampJam__Player__) */
