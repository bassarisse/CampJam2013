//
//  Donut.h
//  CampJam13
//
//  Created by Murilo Clemente - 27/07/13
//
//

#ifndef __CampJam__Donut__
#define __CampJam__Donut__

#include "GameObject.h"

class Donut : public GameObject {
    
private:
    
protected:
    
    virtual void addFixtures();
	

public:
    
    virtual ~Donut();
    
    virtual bool init(b2World *world, Dictionary *properties);
    virtual void update(float dt);

};

#endif /* defined(__PlatformerTest__Player__) */
