//
//  Water.h
//  CampJam13
//
//  Created by Murilo Clemente - 27/07/13
//
//

#ifndef __CampJam__Water__
#define __CampJam__Water__

#include "GameObject.h"

class Water : public GameObject {
    
private:
    
protected:
    
    virtual void addFixtures();

public:
    
    virtual ~Water();
    
    virtual bool init(b2World *world, Dictionary *properties);

};

#endif /* defined(__PlatformerTest__Player__) */
