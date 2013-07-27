
#ifndef __CampJam__Woman__
#define __CampJam__Woman__

#include "Enemy.h"

class Woman : public Enemy {
private:

protected:

	virtual void addFixtures();
    
	virtual void handleCollisions();

public:

	virtual ~Woman();

	virtual bool init(b2World *world, Dictionary *properties, Player* ref);
    virtual void update(float dt);

};


#endif /* defined(__PlatformerTest__Player__) */