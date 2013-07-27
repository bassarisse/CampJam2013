
#ifndef __CampJam__Man__
#define __CampJam__Man__

#include "Enemy.h"

class Man : public Enemy {
private:

protected:

	virtual void addFixtures();
    
	virtual void handleCollisions();

public:

	virtual ~Man();

	virtual bool init(b2World *world, Dictionary *properties);
    virtual void update(float dt);

};


#endif /* defined(__PlatformerTest__Player__) */