//
//  EmptyPaper.cpp
//  CampJam2013
//
//  Created by Bruno Assarisse on 28/07/13.
//
//

#include "EmptyPaper.h"

bool EmptyPaper::init(b2World *world, Dictionary *properties) {
	
	this->setType(GameObjectTypeEmptyPaper);
    
    if (!GameObject::init(world, properties, false, false))
        return false;
    
    return true;
}
