
#ifndef __CampJam__Man__
#define __CampJam__Man__

#include "Enemy.h"

class Man : public Enemy {
private:

protected:

	virtual void addFixtures();

public:

	virtual bool init(b2World *world, Dictionary *properties, Player* ref);
    virtual void die();
    virtual void updatePosition(Point position);

};


#endif /* defined(__CampJam__Player__) */