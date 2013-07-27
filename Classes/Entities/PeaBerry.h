//
//  Peaberry.h
//  CampJam13
//
//  Created by Murilo Clemente - 27/07/13
//
//

#ifndef __CampJam__Peaberry__
#define __CampJam__Peaberry__

#include "GameObject.h"

class Peaberry : public GameObject {
    
private:
    
protected:
    
    virtual void addFixtures();
	

public:
    
    virtual ~Peaberry();
    
    virtual bool init(b2World *world, Dictionary *properties);
    virtual void update(float dt);

};

#endif /* defined(__PlatformerTest__Player__) */
