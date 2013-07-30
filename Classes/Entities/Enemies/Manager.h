
#ifndef __CampJam__Manager__
#define __CampJam__Manager__

#include "Enemy.h"

class Manager : public Enemy {
private:

protected:

	virtual void addFixtures();
    virtual void executeWalkAnimation();

public:

	virtual bool init(b2World *world, Dictionary *properties, Player* ref);
    virtual void die();

};


#endif /* defined(__CampJam__Player__) */