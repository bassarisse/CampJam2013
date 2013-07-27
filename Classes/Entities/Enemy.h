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
#include "Entities/Player.h"

class Enemy : public GameObject {
    
private:
    
protected:
    
    virtual void addFixtures();
	
	virtual void handleCollisions();

	Player* _playerReference;

public:
    
    virtual ~Enemy();
    
    virtual bool init(b2World *world, Dictionary *properties, Player* ref);
    virtual void update(float dt);
    
	float _damageFactor;
	float _coffee;

	virtual void handleMovement();


};

#endif /* defined(__PlatformerTest__Player__) */
