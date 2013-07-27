
#ifndef __CampJam__Manager__
#define __CampJam__Manager__

#include "Enemy.h"

class Manager : public Enemy {
private:

protected:

	virtual void addFixtures();

public:

	virtual ~Manager();

	virtual bool init(b2World *world, Dictionary *properties, Player* ref);

};


#endif /* defined(__CampJam__Player__) */