//
//  PeaBerry.h
//  CampJam13
//
//  Created by Murilo Clemente - 27/07/13
//
//

#ifndef __CampJam__Peaberry__
#define __CampJam__Peaberry__

#include "Collectable.h"

class PeaBerry : public Collectable {
	

public:
    
    virtual bool init(b2World *world, Dictionary *properties);

};

#endif /* defined(__CampJam__Player__) */
