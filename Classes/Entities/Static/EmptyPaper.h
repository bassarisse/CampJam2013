//
//  EmptyPaper.h
//  CampJam2013
//
//  Created by Bruno Assarisse on 28/07/13.
//
//

#ifndef __CampJam2013__EmptyPaper__
#define __CampJam2013__EmptyPaper__

#include "GameObject.h"

class EmptyPaper : public GameObject {
	
public:
    
    virtual bool init(b2World *world, Dictionary *properties);
    
};

#endif /* defined(__CampJam2013__EmptyPaper__) */
