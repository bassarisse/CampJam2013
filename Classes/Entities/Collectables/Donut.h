//
//  Donut.h
//  CampJam13
//
//  Created by Murilo Clemente - 27/07/13
//
//

#ifndef __CampJam__Donut__
#define __CampJam__Donut__

#include "Collectable.h"

class Donut : public Collectable {
	

public:
    
    virtual bool init(b2World *world, Dictionary *properties);

};

#endif /* defined(__CampJam__Player__) */
