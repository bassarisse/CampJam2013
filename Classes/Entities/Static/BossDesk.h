//
//  BossDesk.h
//  CampJam2013
//
//  Created by Bruno Assarisse on 28/07/13.
//
//

#ifndef __CampJam2013__BossDesk__
#define __CampJam2013__BossDesk__

#include "GameObject.h"

class BossDesk : public GameObject {
	
public:
    
    virtual bool init(b2World *world, Dictionary *properties);
    
};

#endif /* defined(__CampJam2013__BossDesk__) */
