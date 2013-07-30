
#ifndef __CampJam__Woman__
#define __CampJam__Woman__

#include "Enemy.h"

class Woman : public Enemy {
private:

protected:

	virtual void addFixtures();

public:

	virtual bool init(b2World *world, Dictionary *properties, Player* ref);
    virtual void die();

};


#endif /* defined(__CampJam__Player__) */